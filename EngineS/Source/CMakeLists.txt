file(GLOB_RECURSE HEADER_FILES "*.hpp")
file(GLOB_RECURSE SOURCE_FILES "*.cpp")

add_executable(EngineS ${SOURCE_FILES} ${HEADER_FILES})

target_link_libraries(EngineS PUBLIC glfw)
target_link_libraries(EngineS PUBLIC glad)
target_link_libraries(EngineS PUBLIC spdlog::spdlog)
target_link_libraries(EngineS PUBLIC ryml::ryml)
target_link_libraries(EngineS PRIVATE stb)

target_include_directories(EngineS PUBLIC .)