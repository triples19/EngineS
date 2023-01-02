#include "Resource/ResourceManager.hpp"
#include "Base/Macros.hpp"
#include "Reflection/Type.hpp"
#include "Resource/Resource.hpp"

#include <fstream>

namespace fs = std::filesystem;

namespace EngineS {

ResourceManager* s_SharedInstance;

ResourceManager* ResourceManager::Instance() {
    if (!s_SharedInstance) {
        s_SharedInstance = new (std::nothrow) ResourceManager;
        ES_ASSERT_NOMSG(s_SharedInstance != nullptr);
        s_SharedInstance->Retain();
    }
    return s_SharedInstance;
}

Resource* ResourceManager::Load(const Type* type, const fs::path& path) {
    // Return one if it has already been loaded
    if (_resources.contains(path)) {
        auto resource = _resources[path];
        if (!type->Is(resource->GetType())) {
            LOG_ERROR(
                "Resource type '{}' does not match the loaded one '{}': {}",
                type->GetName(),
                resource->GetType()->GetName(),
                path.string()
            );
            return nullptr;
        }
        return resource;
    }

    auto absolutePath = FindResourcePath(path);
    if (!absolutePath) {
        LOG_ERROR("File does not exist: {}", path.string());
        return nullptr;
    }

    // Create a object of 'type' and cast it to Resource*
    auto resource = dynamic_cast<Resource*>(type->CreateObject());
    if (!resource) {
        // dynamic_cast failed
        // which means 'type' is not a subclass of Resource
        LOG_ERROR("Could not load resource type: {}", type->GetName());
        return nullptr;
    }

    if (!resource->Load(*absolutePath)) {
        // Load failure
        return nullptr;
    }

    _resources[path] = resource; // Cache it
    resource->Retain();          // Own a reference
    return resource;
}

bool ResourceManager::AddResourceDir(const fs::path& path) {
    if (!fs::is_directory(path)) {
        LOG_ERROR("Could not open directory: {}", path.string());
        return false;
    }

    if (std::find_if(_resourceDirs.begin(), _resourceDirs.end(), [&](const auto& p) {
            return fs::equivalent(path, p);
        }) != _resourceDirs.end()) {
        return true;
    }

    _resourceDirs.push_back(fs::absolute(path));
    return true;
}

std::optional<fs::path> ResourceManager::FindResourcePath(const fs::path& path) const {
    for (const auto& dir : _resourceDirs) {
        auto concated = dir / path;
        if (fs::exists(concated))
            return concated;
    }
    return std::nullopt;
}

} // namespace EngineS