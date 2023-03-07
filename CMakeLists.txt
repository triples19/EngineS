cmake_minimum_required(VERSION 3.10)
project(EngineS)

set(CMAKE_CXX_STANDARD 20)

cmake_policy(SET CMP0091 NEW)

if (MSVC)
    add_compile_options(/wd4267)
    add_compile_options(/wd4244)
endif ()

set(ES_ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${ES_ROOT_DIR}/bin/$<0:>)

add_subdirectory(ThirdParty)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(ES_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Source/EngineS)
add_subdirectory(Source/EngineS)

add_subdirectory(Example)

add_subdirectory(Test)