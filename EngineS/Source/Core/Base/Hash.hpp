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