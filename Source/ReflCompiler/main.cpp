#include "llvm/Support/CommandLine.h"

#include "ReflCompiler.hpp"

using namespace llvm;

cl::opt<std::string> OptBuildPath("p", cl::desc("Build path"), cl::init("."), cl::Required);
cl::opt<std::string> OptSourcePath(cl::Positional, cl::desc("<source path>"));
cl::opt<std::string> OptIncludeRootPath("i", cl::desc("Include root path"), cl::Required);
cl::opt<std::string> OptOutputFile("o", cl::desc("Output file"), cl::init("Generated/Refl.cpp"));

int main(int argc, const char** argv) {
    cl::ParseCommandLineOptions(argc, argv);

    outs() << "Build Path:\t\t" << OptBuildPath << "\n"
           << "Source Path:\t\t" << OptSourcePath << "\n"
           << "Include Root Path:\t" << OptIncludeRootPath << "\n"
           << "Output File:\t\t" << OptOutputFile << "\n";

    auto compiler = ReflCompiler::Create(
        OptSourcePath.getValue(),
        OptBuildPath.getValue(),
        OptIncludeRootPath.getValue(),
        OptOutputFile.getValue()
    );
    if (compiler) {
        compiler->Run();
    }

    return 0;
}