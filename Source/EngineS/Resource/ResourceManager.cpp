#include "Resource/ResourceManager.hpp"
#include "Core/Macros.hpp"
#include "Core/Reflection/ConstructorInfo.hpp"
#include "Core/Reflection/Type.hpp"
#include "Resource/Resource.hpp"

#include <fstream>

namespace fs = std::filesystem;

namespace EngineS {

ResourceManager* s_SharedInstance;

ResourceManager* ResourceManager::Instance() {
    if (!s_SharedInstance) {
        s_SharedInstance = new (std::nothrow) ResourceManager;
        ES_ASSERT(s_SharedInstance != nullptr);
        s_SharedInstance->Retain();
    }
    return s_SharedInstance;
}

void ResourceManager::Update() {
    if (_autoReloadEnabled) {
        for (auto& [_, desc] : _resources) {
            auto time = fs::last_write_time(desc.absolutePath);
            if (time != desc.lastWriteTime) {
                // file modified
                desc.lastWriteTime = time;
                desc.resource->Load(desc.absolutePath);
            }
        }
    }
}

Resource* ResourceManager::Load(const Type* type, const fs::path& path) {
    // Return one if it has already been loaded
    if (_resources.contains(path)) {
        auto resource = _resources[path].resource;
        if (!type->Is(resource->GetType())) {
            Logger::Error(
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
        Logger::Error("File does not exist: {}", path.string());
        return nullptr;
    }

    // Create an object of 'type' and cast it to Resource*
    auto resource = type->GetConstructor({})->Invoke().Convert<Resource*>();
    if (!resource) {
        // dynamic_cast failed
        // which means 'type' is not a subclass of Resource
        Logger::Error("Could not load resource type: {}", type->GetName());
        return nullptr;
    }

    if (!resource->Load(*absolutePath)) {
        // Load failure
        return nullptr;
    }

    resource->Retain(); // Own a reference

    ResourceDescriptor descriptor;
    descriptor.resource      = resource;
    descriptor.relativePath  = path;
    descriptor.absolutePath  = *absolutePath;
    descriptor.lastWriteTime = fs::last_write_time(*absolutePath);
    _resources[path]         = descriptor;

    return resource;
}

bool ResourceManager::AddResourceDir(const fs::path& path) {
    if (!fs::is_directory(path)) {
        Logger::Error("Could not open directory: {}", path.string());
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
