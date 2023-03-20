#include "ReflCompiler.hpp"
#include "ExBustache.hpp"

#include <algorithm>
#include <clang/AST/QualTypeNames.h>
#include <fstream>
#include <llvm/Support/ThreadPool.h>
#include <sstream>

using namespace llvm;
using namespace clang::tooling;
using namespace llvm::sys;
using namespace clang::ast_matchers;
using namespace clang;

auto ObjectMatcher = cxxRecordDecl(
                         isExpansionInMainFile(),
                         isDefinition(),
                         has(decl(anyOf(isExpandedFromMacro("ES_OBJECT"), isExpandedFromMacro("ES_REFL_ENABLE"))))
)
                         .bind("objectClassDecl");

void ObjectMatchCallback::run(const clang::ast_matchers::MatchFinder::MatchResult& Result) {
    auto            node = Result.Nodes.getNodeAs<clang::CXXRecordDecl>("objectClassDecl");
    ObjectClassInfo info;

    clang::PrintingPolicy printingPolicy(Result.Context->getLangOpts());
    printingPolicy.adjustForCPlusPlus();

    auto getTypeName = [&](const QualType& type) {
        return clang::TypeName::getFullyQualifiedName(type.getCanonicalType(), *Result.Context, printingPolicy);
    };

    auto parseParams = [&](const auto& params) {
        std::vector<ParameterInfo> ret;
        for (auto param : params) {
            ParameterInfo parameterInfo {
                .typeName  = getTypeName(param->getType()),
                .paramName = param->getNameAsString(),
            };
            ret.push_back(parameterInfo);
        }
        return ret;
    };

    // Get qualified name e.g. EngineS::Resource
    info.className = node->getQualifiedNameAsString();

    // Bases
    for (auto base : node->bases()) {
        info.bases.push_back(BaseInfo {
            .baseName = getTypeName(base.getType()),
        });
    }

    for (auto ctor : node->ctors()) {
        if (ctor->isDeleted()) {
            continue;
        }
        info.constructors.emplace_back(ConstructorInfo {.params = parseParams(ctor->parameters())});
    }

    // Methods including constructors
    for (auto method : node->methods()) {
        if (method->getAccess() == AccessSpecifier::AS_private || method->getAccess() == clang::AS_protected) {
            // Private / Protected members
            continue;
        } else if (method->getDeclKind() == clang::Decl::CXXConstructor) {
            // Constructor
            continue;
        } else if (method->getDeclKind() == clang::Decl::CXXDestructor) {
            // Destructor
            continue;
        } else if (method->getOverloadedOperator()) {
            // Overloaded operator
            continue;
        }

        // Regular methods
        info.methods.emplace_back(MethodInfo {
            .methodName     = method->getNameAsString(),
            .returnTypeName = getTypeName(method->getReturnType()),
            .isStatic       = method->isStatic(),
            .isConst        = method->isConst(),
            .params         = parseParams(method->parameters()),
        });
    }

    for (auto field : node->fields()) {
        if (field->getAccess() != AccessSpecifier::AS_public) {
            // Private / Protected members
            continue;
        }
        FieldInfo fieldInfo {
            .fieldName = field->getNameAsString(),
            .typeName  = getTypeName(field->getType()),
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
    const std::filesystem::path& outputPath,
    const std::filesystem::path& outputJsonPath
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
    ptr->_outputJsonPath  = outputJsonPath;
    return ptr;
}

void ReflCompiler::Run() {
    std::mutex objectsMutex, outsMutex;
    int        index = 1, len = _sources.size();

    auto runLambda = [&](const std::filesystem::path& source) {
        auto relativePathStr = std::filesystem::relative(source, _includeRootPath).string();
        std::replace(relativePathStr.begin(), relativePathStr.end(), '\\', '/');

        //        // check whether the file has ES_OBJECT
        //        // if not, we just ignore the file for speed
        //        bool hasObjectMacro = [source]() -> bool {
        //            std::ifstream inFile(source);
        //            std::string   lineBuf;
        //            while (std::getline(inFile, lineBuf)) {
        //                if (lineBuf.find("ES_OBJECT") != std::string::npos) {
        //                    return true;
        //                }
        //            }
        //            return false;
        //        }();
        //        if (!hasObjectMacro)
        //            return;

        ClangTool           tool(*_compilationDB, {source.string()});
        ObjectMatchCallback callback;
        MatchFinder         finder;
        finder.addMatcher(ObjectMatcher, &callback);
        tool.run(newFrontendActionFactory(&finder).get());

        std::unique_lock lk(objectsMutex);
        // retrieve matched objects
        for (auto info : callback.GetObjectInfos()) {
            info.filePath = relativePathStr;
            _objects.push_back(info);
        }
        lk.unlock();

        std::unique_lock outsLk {outsMutex};
        fmt::print("[{}/{}] Compiled {}\n", index++, len, relativePathStr);
        outsLk.unlock();
    };
    // std::for_each(std::execution::par_unseq, _sources.begin(), _sources.end(), runLambda);
    ThreadPool pool;
    for (const auto& source : _sources) {
        pool.async(runLambda, source);
    }
    pool.wait();

    // running this in parallel will result in different order per run
    // we don't care about the order, but it's best to result in the same when nothing changes
    std::sort(_objects.begin(), _objects.end(), [](const auto& a, const auto& b) { return a.className < b.className; });

    outs() << "Writing " << _outputPath.string() << "\n";

    nlohmann::json json = {{"objects", _objects}};

    // .\ReflCompiler.exe -t ..\Source\Templates\EngineObjects.mustache -p ..\build\ -o .\Test.cpp -i ..\Source\EngineS\ ..\Source\EngineS\

    if (_outputJsonPath != "") {
        std::ofstream outJson(_outputJsonPath);
        outJson << json.dump(2);
    }

    bustache::format fmt(_template);
    std::ofstream    outFile(_outputPath);
    outFile << fmt(json);
}
