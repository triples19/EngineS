find_package(LLVM REQUIRED CONFIG)
find_package(Clang REQUIRED CONFIG)

add_executable(ReflCompiler
    main.cpp
    ReflCompiler.cpp
    ReflCompiler.hpp
    BustacheNlohmann.hpp
    Template.hpp
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

target_compile_definitions(ReflCompiler PRIVATE "_ITERATOR_DEBUG_LEVEL=0")
target_compile_definitions(bustache PRIVATE "_ITERATOR_DEBUG_LEVEL=0")
target_compile_definitions(fmt PRIVATE "_ITERATOR_DEBUG_LEVEL=0")
if (MSVC)
    target_compile_options(ReflCompiler PRIVATE /MD /wd4267 /wd4244 /wd4819 /wd4624 /wd4291 /wd4146)
    target_compile_options(bustache PRIVATE /MD)
    target_compile_options(fmt PRIVATE /MD)
endif ()