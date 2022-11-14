add_executable(Example
        main.cpp
        TestScene.cpp
        TestComponent.cpp)

target_link_libraries(Example EngineS)

set(ASSETS_ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Assets)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)