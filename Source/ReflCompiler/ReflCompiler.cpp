#include "ReflCompiler.hpp"
#include "BustacheNlohmann.hpp"

#include <algorithm>
#include <execution>
#include <fstream>
#include <sstream>

using namespace llvm;
using namespace clang::tooling;
using namespace llvm::sys;
using namespace clang::ast_matchers;
using namespace clang;

auto ObjectMatcher = cxxRecordDecl(
                         isExpansionInMainFile(),
                         isDefinition(),
                         isDerivedFrom(hasName("EngineS::Object")),
                         has(varDecl(hasName("__es_type"), isExpandedFromMacro("ES_OBJECT")))
)
                         .bind("objectClassDecl");

void ObjectMatchCallback::run(const clang::ast_matchers::MatchFinder::MatchResult& Result) {
    auto            node = Result.Nodes.getNodeAs<clang::CXXRecordDecl>("objectClassDecl");
    ObjectClassInfo info;
    // get qualified name e.g. EngineS::Resource
    info.className = node->getQualifiedNameAsString();
    // get first base class name
    // assuming it's derived from or is EngineS::Object
    info.baseName = node->bases_begin()->getType().getAsString();

    for (auto method : node->methods()) {
        if (method->getDeclKind() == clang::Decl::CXXConstructor) {
            // Constructor
            continue;
        } else if (method->getDeclKind() == clang::Decl::CXXDestructor) {
            // Destructor
            continue;
        } else if (method->getOverloadedOperator()) {
            // Overloaded operator
            continue;
        }

        MethodInfo methodInfo;
        methodInfo.methodName     = method->getNameAsString();
        methodInfo.returnTypeName = method->getReturnType().getAsString();
        methodInfo.isStatic       = method->isStatic();
        methodInfo.isConst        = method->isConst();
        for (auto param : method->parameters()) {
            ParameterInfo parameterInfo {
                .typeName  = param->getType().getAsString(),
                .paramName = param->getNameAsString(),
            };
            methodInfo.params.push_back(parameterInfo);
        }
        info.methods.push_back(methodInfo);
    }

    for (auto field : node->fields()) {
        FieldInfo fieldInfo {
            .fieldName = field->getNameAsString(),
            .typeName  = field->getType().getAsString(),
        };
        info.fields.push_back(fieldInfo);
    }

    _infos.push_back(info);
}

std::unique_ptr<ReflCompiler> ReflCompiler::Create(
    const std::filesystem::path& sourcePath,
    const std::filesystem::path& buildPath,
    const std::filesystem::path& includeRootPath,
    const std::filesystem::path& templatePath,
    const std::filesystem::path& outputPath
) {
    // -- check include root path ---
    if (!std::filesystem::is_directory(includeRootPath)) {
        errs() << "Include root path does not exist\n";
        return nullptr;
    }

    // --- get compilation database (compile_commands.json) ---
    std::string errorMsg;
    auto        compilations = std::make_unique<ArgumentsAdjustingCompilations>(
        std::move(CompilationDatabase::autoDetectFromDirectory(buildPath.string(), errorMsg))
    );
    compilations->appendArgumentsAdjuster(getInsertArgumentAdjuster("-DREFL_COMPILER", ArgumentInsertPosition::BEGIN));

    if (!compilations) {
        errs() << errorMsg;
        return nullptr;
    }

    // --- get header files ---
    if (!std::filesystem::is_directory(sourcePath)) {
        errs() << "Source path does not exist\n";
        return nullptr;
    }
    std::vector<std::filesystem::path> sources;
    for (const auto& entry : std::filesystem::recursive_directory_iterator(sourcePath)) {
        if (entry.is_regular_file() && entry.path().extension() == ".hpp") {
            sources.push_back(entry.path());
        }
    }

    // --- read template ---
    if (!std::filesystem::is_regular_file(templatePath)) {
        errs() << "Template file does not exist\n";
        return nullptr;
    }
    auto readFile = [](const std::filesystem::path& path) {
        std::ifstream     file(path);
        std::stringstream ss;
        ss << file.rdbuf();
        return ss.str();
    };
    auto templateStr = readFile(templatePath);

    auto ptr              = std::make_unique<ReflCompiler>();
    ptr->_compilationDB   = std::move(compilations);
    ptr->_sources         = std::move(sources);
    ptr->_includeRootPath = includeRootPath;
    ptr->_template        = std::move(templateStr);
    ptr->_outputPath      = outputPath;
    return ptr;
}

void ReflCompiler::Run() {
    std::mutex objectsMutex, outsMutex;
    auto       runLambda = [&](const std::filesystem::path& source) {
        auto relativePathStr = std::filesystem::relative(source, _includeRootPath).string();
        std::replace(relativePathStr.begin(), relativePathStr.end(), '\\', '/');

        std::unique_lock outsLk {outsMutex, std::defer_lock};
        outsLk.lock();
        outs() << "Searching in " << relativePathStr << "...\n";
        outsLk.unlock();

        // check whether the file has ES_OBJECT
        // if not, we just ignore the file for speed
        bool hasObjectMacro = [source]() -> bool {
            std::ifstream inFile(source);
            std::string   lineBuf;
            while (std::getline(inFile, lineBuf)) {
                if (lineBuf.find("ES_OBJECT") != std::string::npos) {
                    return true;
                }
            }
            return false;
        }();
        if (!hasObjectMacro)
            return;

        ClangTool           tool(*_compilationDB, {source.string()});
        ObjectMatchCallback callback;
        MatchFinder         finder;
        finder.addMatcher(ObjectMatcher, &callback);
        tool.run(newFrontendActionFactory(&finder).get());

        std::lock_guard lk(objectsMutex);
        // retrieve matched objects
        for (auto info : callback.getObjectInfos()) {
            outsLk.lock();
            outs() << "Found: " << info.className << "\n";
            outsLk.unlock();
            info.filePath = relativePathStr;
            _objects.push_back(info);
        }
    };
    std::for_each(std::execution::par_unseq, _sources.begin(), _sources.end(), runLambda);

    // running this in parallel will result in different order per run
    // we don't care about the order, but it's best to result in the same when nothing changes
    std::sort(_objects.begin(), _objects.end(), [](const auto& a, const auto& b) { return a.className < b.className; });

    outs() << "Writing " << _outputPath.string() << "\n";

    nlohmann::json json = {{"objects", _objects}};

    // .\ReflCompiler.exe -t ..\Source\Templates\EngineObjects.mustache -p ..\build\ -o .\Test.cpp -i ..\Source\EngineS\ ..\Source\EngineS\

    //    outs() << json.dump(2);

    bustache::format fmt(_template);
    std::ofstream    outFile(_outputPath);
    outFile << fmt(json);
}
