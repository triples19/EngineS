add_library(
        bustache
        ${CMAKE_CURRENT_LIST_DIR}/bustache/src/format.cpp
        ${CMAKE_CURRENT_LIST_DIR}/bustache/src/render.cpp
)

target_compile_features(bustache PUBLIC cxx_std_20)

target_include_directories(bustache PUBLIC ${CMAKE_CURRENT_LIST_DIR}/bustache/include)

target_link_libraries(bustache PUBLIC fmt::fmt)
target_compile_definitions(bustache PUBLIC BUSTACHE_USE_FMT)

add_library(bustache::bustache ALIAS bustache)