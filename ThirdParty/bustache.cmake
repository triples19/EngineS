add_library(
  bustache
  bustache/src/format.cpp
  bustache/src/render.cpp
)

target_compile_features(bustache PUBLIC cxx_std_20)

target_include_directories(bustache PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/bustache/include)

target_link_libraries(bustache PUBLIC fmt::fmt)
target_compile_definitions(bustache PUBLIC BUSTACHE_USE_FMT)

add_library(bustache::bustache ALIAS bustache)