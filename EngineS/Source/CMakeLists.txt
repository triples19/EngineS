file(GLOB_RECURSE HEADER_FILES "*.hpp")
file(GLOB_RECURSE SOURCE_FILES "*.cpp")

add_executable(EngineS ${SOURCE_FILES} ${HEADER_FILES})