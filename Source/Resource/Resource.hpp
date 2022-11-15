#pragma once

#include "Base/Object.hpp"
#include "MetaData.hpp"

#include <filesystem>
#include <fstream>
#include <sstream>
namespace fs = std::filesystem;

namespace EngineS {

/**
 * @brief Resource / Asset
 */
class Resource : public Object {};

/**
 * @brief A handle of some resource.
 */
class ResourceHandleBase : public Object {
    friend class ResourceManager;

  public:
    ResourceHandleBase()          = default;
    virtual ~ResourceHandleBase() = default;
    size_t ID;

  private:
    ResourceHandleBase(size_t id) : ID {id} {}
};

/**
 * @brief A facotry class for creating and reloading the resource.
 *
 */
class ResourceLoader : public Object {
  public:
    virtual Resource* CreateResource(const fs::path& path) const = 0;
    virtual void      ReloadResource(std::shared_ptr<Resource>& resource, const fs::path& path) const {
        resource.reset(CreateResource(path));
    }
    virtual std::string GetName() const = 0;

  protected:
    std::string ReadString(const fs::path& path) const {
        std::ifstream     file(path);
        std::stringstream ss;
        ss << file.rdbuf();
        return ss.str();
    }
};

} // namespace EngineS