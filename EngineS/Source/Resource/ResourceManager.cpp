#include "ResourceManager.hpp"

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
	for (auto& [id, lastWriteTime] : _watchedHandles) {
		auto currentLastWriteTime = fs::last_write_time(_handles.at(id).path);
		if (currentLastWriteTime != lastWriteTime) {
			// file modified
			ReloadResource(ResourceHandleBase {id});
			lastWriteTime = currentLastWriteTime;
		}
	}
}

void ResourceManager::AddHandle(const fs::path& metaPath, const fs::path& resourcePath) {
	auto		id = GetNextID();
	MetaData	meta(metaPath);
	const auto& loader = *_loaders[meta.GetLoaderName()];
	_handles.try_emplace(id, resourcePath, std::move(meta));
	_pathToID.emplace(fs::absolute(resourcePath), id);
}

void ResourceManager::AddAllHandles() {
	for (const auto& dirEntry : fs::recursive_directory_iterator(_assetsPath)) {
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

void ResourceManager::AddWatch(const ResourceHandleBase& handle) {
	if (_watchedHandles.find(handle.ID) != _watchedHandles.end()) {
		return;
	}
	_watchedHandles.emplace(handle.ID, fs::last_write_time(_handles.at(handle.ID).path));
}

void ResourceManager::RemoveWatch(const ResourceHandleBase& handle) {
	_watchedHandles.erase(handle.ID);
}

ResourceLoader* ResourceManager::GetLoader(const ResourceHandleBase& handle) {
	auto loaderName = _handles.at(handle.ID).meta.GetLoaderName();
	auto iter		= _loaders.find(loaderName);
	if (iter == _loaders.end()) {
		LOG_ERROR("Unregistered loader: {}", loaderName);
		return nullptr;
	}
	return iter->second.get();
}

void ResourceManager::LoadResource(const ResourceHandleBase& handle) {
	const auto& loader	 = GetLoader(handle);
	auto		resource = loader->CreateResource(_handles.at(handle.ID).path);
	_cache.emplace(handle.ID, resource);
}

void ResourceManager::UnloadResource(const ResourceHandleBase& handle) {
	_cache.erase(handle.ID);
}

void ResourceManager::ReloadResource(const ResourceHandleBase& handle) {
	auto		iter   = _cache.find(handle.ID);
	const auto& loader = GetLoader(handle);
	loader->ReloadResource(iter->second, _handles.at(handle.ID).path);
}

void ResourceManager::UnloadUnusedResources() {
	std::erase_if(_cache, [](const auto& item) {
		auto const& [handle, resource] = item;
		return resource.use_count() == 1;
	});
}

std::shared_ptr<Resource> ResourceManager::GetLoadedResource(const ResourceHandleBase& handle) {
	auto iter = _cache.find(handle.ID);
	if (iter == _cache.end()) {
		LOG_ERROR("Unloaded resource: {}", _handles.at(handle.ID).path.string());
		return nullptr;
	}
	return iter->second;
}

} // namespace EngineS
