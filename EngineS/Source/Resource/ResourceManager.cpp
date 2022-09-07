#include "ResourceManager.hpp"

#include "Core/Base/Macros.hpp"

#include "Function/Render/Program.hpp"
#include "Function/Render/Texture2D.hpp"
#include "Resource/CommonResources/Text.hpp"

#include <algorithm>

namespace EngineS {

void ResourceManager::Initialize() {
	RegisterLoader<TextLoader>();
	RegisterLoader<ProgramLoader>();
	RegisterLoader<Texture2DLoader>();

	AddAllHandles();
}

void ResourceManager::Update() {
	for (auto& [handle, lastWriteTime] : _watchedHandles) {
		auto currentLastWriteTime = fs::last_write_time(handle->GetPath());
		if (currentLastWriteTime != lastWriteTime) {
			// file modified
			ReloadResource(handle);
			lastWriteTime = currentLastWriteTime;
		}
	}
}

void ResourceManager::AddHandle(const fs::path& metaPath, const fs::path& resourcePath) {
	auto		meta   = std::make_shared<MetaData>(metaPath);
	const auto& loader = *_loaders[meta->GetLoaderName()];
	auto		handle = std::make_unique<ResourceHandle>(meta, resourcePath);
	_handles.emplace(resourcePath, std::move(handle));
}

void ResourceManager::AddAllHandles() {
	fs::path assetPath = "Assets";
	for (const auto& dirEntry : fs::recursive_directory_iterator(assetPath)) {
		const auto& path = std::filesystem::absolute(dirEntry.path());
		if (path.extension() == ".meta") {
			auto originPath = path;
			originPath.replace_extension();
			if (exists(originPath)) {
				AddHandle(path, originPath);
			}
		}
	}
}

void ResourceManager::AddWatch(ResourceHandle* handle) {
	if (_watchedHandles.find(handle) != _watchedHandles.end()) {
		return;
	}
	_watchedHandles.emplace(handle, fs::last_write_time(handle->GetPath()));
}

void ResourceManager::RemoveWatch(ResourceHandle* handle) {
	_watchedHandles.erase(handle);
}

ResourceHandle* ResourceManager::GetHandle(const fs::path& path) {
	auto absolutePath = fs::absolute(fs::path("Assets") / path);
	return _handles[absolutePath].get();
}

ResourceLoader* ResourceManager::GetLoader(ResourceHandle* handle) {
	auto loaderName = handle->GetMetaData().GetLoaderName();
	auto iter		= _loaders.find(loaderName);
	if (iter == _loaders.end()) {
		LOG_ERROR("Unregistered loader: {}", loaderName);
		return nullptr;
	}
	return iter->second.get();
}

void ResourceManager::LoadResource(ResourceHandle* handle) {
	const auto& loader	 = GetLoader(handle);
	auto		resource = loader->CreateResource(handle->GetPath());
	_cache.emplace(handle, resource);
}

void ResourceManager::UnloadResource(ResourceHandle* handle) {
	_cache.erase(handle);
}

void ResourceManager::ReloadResource(ResourceHandle* handle) {
	auto		iter   = _cache.find(handle);
	const auto& loader = GetLoader(handle);
	loader->ReloadResource(iter->second, handle->GetPath());
}

void ResourceManager::UnloadUnusedResources() {
	std::erase_if(_cache, [](const auto& item) {
		auto const& [handle, resource] = item;
		return resource.use_count() == 1;
	});
}

std::shared_ptr<Resource> ResourceManager::GetLoadedResource(ResourceHandle* handle) {
	auto iter = _cache.find(handle);
	if (iter == _cache.end()) {
		LOG_ERROR("Unloaded resource: {}", handle->GetPath().string());
		return nullptr;
	}
	return iter->second;
}

} // namespace EngineS
