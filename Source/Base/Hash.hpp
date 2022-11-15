#pragma once

#include <cstddef>
#include <filesystem>
namespace fs = std::filesystem;

template<class>
struct Hasher;

template<>
struct Hasher<fs::path> {
    std::size_t operator()(const fs::path& path) const { return fs::hash_value(path); }
};

template<typename T, typename... Rest>
void HashCombine(std::size_t& seed, const T& v, const Rest&... rest) {
    seed ^= std::hash<T> {}(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
    (HashCombine(seed, rest), ...);
}