#pragma once

#include "Resource/Resource.hpp"

#include <sstream>

namespace EngineS {

class Text : public Resource {
    ES_OBJECT
  public:
    virtual bool Load(const std::filesystem::path& path) override {
        std::ifstream     inStream(path);
        std::stringstream ss;
        ss << inStream.rdbuf();
        _text = ss.str();
        return true;
    }
    const std::string& GetText() const { return _text; }

  private:
    std::string _text;
};

} // namespace EngineS
