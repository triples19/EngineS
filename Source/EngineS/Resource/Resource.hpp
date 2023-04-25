#pragma once

#include "Core/Object.hpp"

#include <filesystem>
#include <fstream>

namespace EngineS {

class Resource : public Object {
    ES_OBJECT
  public:
    virtual bool Load(const std::filesystem::path& path) { return false; }
};

} // namespace EngineS