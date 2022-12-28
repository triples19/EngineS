#pragma once

#include "Base/PrimitiveTypes.hpp"

#include <cstddef>
#include <filesystem>

namespace EngineS {

template<class T>
struct Hasher {
    hash32 operator()(const T& obj) const { return std::hash<T> {}(obj); }
};

template<>
struct Hasher<std::filesystem::path> {
    hash32 operator()(const std::filesystem::path& path) const { return std::filesystem::hash_value(path); }
};

template<typename T, typename... Rest>
inline void HashCombine(hash32& seed, const T& v, const Rest&... rest) {
    seed ^= std::hash<T> {}(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
    (HashCombine(seed, rest), ...);
}

/**
 * Update a hash with the given 8-bit value using the SDBM algorithm.
 */
inline constexpr hash32 SDBMHash(hash32 hash, u8 c) {
    return c + (hash << 6u) + (hash << 16u) - hash;
}

} // namespace EngineS