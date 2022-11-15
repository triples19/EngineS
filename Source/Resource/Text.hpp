#pragma once

#include "Resource/Resource.hpp"

#include <fstream>
#include <memory>
#include <sstream>
#include <string>

namespace EngineS {

class Text : public Resource {
  public:
    Text(const std::string& str) : _str(str) {}

    const std::string& GetText() const { return _str; }

  private:
    std::string _str;
};

class TextLoader : public ResourceLoader {
  public:
    virtual Resource* CreateResource(const fs::path& path) const override {
        auto resource = new Text(ReadString(path));
        return resource;
    }
    virtual std::string GetName() const override { return "TextLoader"; }
};

} // namespace EngineS