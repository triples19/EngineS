set(ASSETS_ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Assets)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin/$<0:>)

add_executable(Example
        main.cpp
        Generated/Refl.cpp
        TestScene.cpp
        TestComponent.cpp)

target_link_libraries(Example PRIVATE EngineS)
target_include_directories(Example PRIVATE .)