file(GLOB_RECURSE HEADER_FILES "*.hpp")
file(GLOB_RECURSE SOURCE_FILES "*.cpp")

add_library(EngineS ${SOURCE_FILES})

if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    target_link_libraries(EngineS PRIVATE -static)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_link_libraries(EngineS PRIVATE -static-libgcc -static-libstdc++)
endif ()

if (APPLE)
    target_link_libraries(EngineS PRIVATE
            "-framework Cocoa"
            "-framework OpenGL"
            "-framework IOKit"
            "-framework CoreVideo")
endif ()

target_link_libraries(EngineS PUBLIC glfw)
target_link_libraries(EngineS PUBLIC glad)
target_link_libraries(EngineS PUBLIC spdlog::spdlog)
target_link_libraries(EngineS PUBLIC nlohmann_json::nlohmann_json)
target_link_libraries(EngineS PRIVATE stb)

target_include_directories(EngineS PUBLIC .)

target_compile_definitions(EngineS PUBLIC GLFW_INCLUDE_NONE)