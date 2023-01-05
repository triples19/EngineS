cmake_minimum_required(VERSION 3.10)
project(ReflCompiler)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../../../bin/$<0:>)

find_package(LLVM REQUIRED CONFIG)
find_package(Clang REQUIRED CONFIG)

include(../../ThirdParty/bustache.cmake)
add_subdirectory(../../ThirdParty/fmt fmt)
add_subdirectory(../../ThirdParty/json json)

add_executable(ReflCompiler
        main.cpp
        ReflCompiler.cpp
        ReflCompiler.hpp
        BustacheNlohmann.hpp
        Template.hpp
        Template.mustache
        )

target_link_libraries(ReflCompiler PRIVATE
        clangTooling
        clangFrontend
        clangSerialization
        clangToolingCore
        clangASTMatchers
        clangAST
        clangBasic
        LLVMSupport
        LLVMCore
        bustache
        nlohmann_json::nlohmann_json
        )

target_include_directories(ReflCompiler PRIVATE ${LLVM_INCLUDE_DIRS})
separate_arguments(LLVM_DEFINITIONS_LIST NATIVE_COMMAND ${LLVM_DEFINITIONS})
target_compile_definitions(ReflCompiler PRIVATE ${LLVM_DEFINITIONS_LIST})

if (MSVC)
    target_compile_options(ReflCompiler PRIVATE /wd4267 /wd4244 /wd4819 /wd4624 /wd4291 /wd4146)
endif ()