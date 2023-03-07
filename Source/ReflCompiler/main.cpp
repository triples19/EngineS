#include <llvm/Support/CommandLine.h>

#include "ReflCompiler.hpp"

using namespace llvm;

cl::opt<std::string> OptBuildPath("p", cl::desc("Build path"), cl::init("."), cl::Required);
cl::opt<std::string> OptSourcePath(cl::Positional, cl::desc("<source path>"));
cl::opt<std::string> OptIncludeRootPath("i", cl::desc("Include root path"), cl::Required);
cl::opt<std::string> OptTemplateFile("t", cl::desc("Template file"), cl::Required);
cl::opt<std::string> OptOutputFile("o", cl::desc("Output file"), cl::init("Generated/Refl.cpp"));
cl::opt<std::string> OptOutputJsonFile("j", cl::desc("Output JSON file"), cl::init(""));

int main(int argc, const char** argv) {
    cl::ParseCommandLineOptions(argc, argv);

    outs() << "Build Path:        " << OptBuildPath << "\n"
           << "Source Path:       " << OptSourcePath << "\n"
           << "Include Root Path: " << OptIncludeRootPath << "\n"
           << "TemplateFile:      " << OptTemplateFile << "\n"
           << "Output File:       " << OptOutputFile << "\n"
           << "Output JSON File:  " << OptOutputJsonFile << "\n";

    auto compiler = ReflCompiler::Create(
        OptSourcePath.getValue(),
        OptBuildPath.getValue(),
        OptIncludeRootPath.getValue(),
        OptTemplateFile.getValue(),
        OptOutputFile.getValue(),
        OptOutputJsonFile.getValue()
    );
    if (compiler) {
        compiler->Run();
    }

    return 0;
}