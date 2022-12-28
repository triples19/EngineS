#pragma once

#include "Base/Object.hpp"

#include <filesystem>
#include <nlohmann/json.hpp>

namespace EngineS {

class MetaData {
  public:
    MetaData(const std::filesystem::path& path);

    std::string GetLoaderName() const { return _json["loader"]; }

  private:
    nlohmann::json _json;
};

} // namespace EngineS
