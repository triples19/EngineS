#pragma once

#include <filesystem>
#include <string>

namespace EngineS {

namespace FileUtils {

std::string ReadFileStr(const std::filesystem::path& path);

}

} // namespace EngineS