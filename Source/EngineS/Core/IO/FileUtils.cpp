#include "FileUtils.hpp"

#include <fstream>
#include <sstream>

namespace EngineS {

std::string FileUtils::ReadFileStr(const std::filesystem::path& path) {
    std::fstream      inFile(path);
    std::stringstream ss;
    ss << inFile.rdbuf();
    return ss.str();
}

} // namespace EngineS
