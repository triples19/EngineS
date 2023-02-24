#pragma once

#include <clang/ASTMatchers/ASTMatchers.h>
#include <clang/ASTMatchers/ASTMatchFinder.h>
#include <clang/Frontend/FrontendAction.h>
#include <clang/Tooling/CommonOptionsParser.h>
#include <clang/Tooling/CompilationDatabase.h>
#include <clang/Tooling/Tooling.h>

#include <filesystem>
#include <string>

#include <nlohmann/json.hpp>

struct ParameterInfo {
    std::string typeName;
    std::string paramName;
    NLOHMANN_DEFINE_TYPE_INTRUSIVE(ParameterInfo, typeName, paramName)
};

struct MethodInfo {
    std::string                methodName;
    std::string                returnTypeName;
    bool                       isStatic;
    bool                       isConst;
    std::vector<ParameterInfo> params;
    NLOHMANN_DEFINE_TYPE_INTRUSIVE(MethodInfo, methodName, returnTypeName, isStatic, isConst, params)
};

struct FieldInfo {
    std::string fieldName;
    std::string typeName;
    NLOHMANN_DEFINE_TYPE_INTRUSIVE(FieldInfo, fieldName, typeName)
};

struct ObjectClassInfo {
    std::string             className; // name of the class
    std::string             baseName;  // name of the base class (derived from or is Object)
    std::string             filePath;  // file path relative to EngineS's include dir
    std::vector<MethodInfo> methods;
    std::vector<FieldInfo>  fields;
    NLOHMANN_DEFINE_TYPE_INTRUSIVE(ObjectClassInfo, className, baseName, filePath, methods, fields)
};

class ObjectMatchCallback : public clang::ast_matchers::MatchFinder::MatchCallback {
  public:
    virtual void run(const clang::ast_matchers::MatchFinder::MatchResult& Result);

    const std::vector<ObjectClassInfo>& getObjectInfos() const { return _infos; }

  private:
    std::vector<ObjectClassInfo> _infos;
};

class ReflCompiler {
  public:
    static std::unique_ptr<ReflCompiler> Create(
        const std::filesystem::path& sourcePath,
        const std::filesystem::path& buildPath,
        const std::filesystem::path& includeRootPath,
        const std::filesystem::path& templatePath,
        const std::filesystem::path& outputPath
    );

    void Run();

  private:
    std::unique_ptr<clang::tooling::CompilationDatabase> _compilationDB;
    std::vector<std::filesystem::path>                   _sources;
    std::vector<ObjectClassInfo>                         _objects;
    std::filesystem::path                                _includeRootPath;
    std::filesystem::path                                _outputPath;
    std::string                                          _template;
};