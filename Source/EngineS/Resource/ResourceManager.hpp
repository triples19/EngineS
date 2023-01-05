#pragma once

#include "Base/Hash.hpp"
#include "Base/Object.hpp"
#include "Resource/MetaData.hpp"

#include <filesystem>
#include <fstream>
#include <optional>
#include <unordered_map>

namespace EngineS {

class Resource;

class ResourceManager : public Object {
    ES_OBJECT
  public:
    struct ResourceDescriptor {
        Resource*                       resource;
        std::filesystem::path           absolutePath;
        std::filesystem::path           relativePath;
        std::filesystem::file_time_type lastWriteTime;
    };

    static ResourceManager* Instance();

    void Update();

    Resource* Load(const Type* type, const std::filesystem::path& path);

    template<class T>
    T* Load(const std::filesystem::path& path) {
        return static_cast<T*>(Load(T::GetTypeStatic(), path));
    }

    bool AddResourceDir(const std::filesystem::path& path);

    std::optional<std::filesystem::path> FindResourcePath(const std::filesystem::path& path) const;

    void SetAutoReload(bool value) { _autoReloadEnabled = value; }

  private:
    std::unordered_map<std::filesystem::path, ResourceDescriptor, Hasher<std::filesystem::path>> _resources;

    std::vector<std::filesystem::path> _resourceDirs;

    bool _autoReloadEnabled {false};
};

} // namespace EngineS