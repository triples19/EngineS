#include "MetaData.hpp"

#include <fstream>
#include <sstream>

namespace EngineS {

MetaData::MetaData(const std::filesystem::path& path) {
    std::ifstream file(path);
    _json = nlohmann::json::parse(file);
}

} // namespace EngineS