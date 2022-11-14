#pragma once

#include "Core/Base/Hash.hpp"
#include "Core/Base/Macros.hpp"
#include "Resource/Resource.hpp"

#include <concepts>
#include <filesystem>
#include <memory>
#include <string>
#include <unordered_map>

namespace fs = std::filesystem;

namespace EngineS {

template<class T>
	requires std::derived_from<T, Resource>
class ResourceHandle;

/**
 * A handle-based resource management system
 *
 * Supports:
 *  - Automatically search for all the metadata and load them in
 *  - Load/Unload resource with handle
 *  - Watch for file modification and reloads it at runtime
 *  - User-defined resources and loaders
 *
 * TODO:
 *  - Better memory allocation (custom memory pool)
 *  - Managing bulitin resources
 */
class ResourceManager {
  public:
	static ResourceManager* Instance();

	/**
	 * @brief Initialze the manager, loading all the metadata into memory
	 */
	void Initialize();

	/**
	 * @brief Check for file modifications
	 */
	void Update();

	/**
	 * @brief Register a resource loader
	 *
	 * @tparam T a subclass of ResourceLoader
	 */
	template<class T>
		requires std::derived_from<T, ResourceLoader>
	void RegisterLoader() {
		auto loader = std::make_unique<T>();
		_loaders.emplace(loader->GetName(), std::move(loader));
	}

	/**
	 * @brief Loads a handle from the disk
	 *
	 * @param metaPath The path of .meta file
	 * @param resourcePath The path of the resource file
	 */
	void AddHandle(const fs::path& metaPath, const fs::path& resourcePath);

	/**
	 * @brief Loads all metadata files under the Assets folder
	 */
	void AddAllHandles();

	/**
	 * @brief Adds file modification watch for a handle
	 */
	void AddWatch(const ResourceHandleBase& handle);

	/**
	 * @brief Remove file modification watch for a handle
	 */
	void RemoveWatch(const ResourceHandleBase& handle);

	template<class T>
		requires std::derived_from<T, Resource>
	ResourceHandle<T> GetHandle(const fs::path& path);

	/**
	 * @brief Get the ResourceLoader by handle
	 *
	 * @param handle The resource handle
	 * @return ResourceLoader* A weak pointer to the loader
	 */
	ResourceLoader* GetLoader(const ResourceHandleBase& handle);

	/**
	 * @brief Load the resource from the disk
	 *
	 * @param handle The handle of the resource
	 */
	void LoadResource(const ResourceHandleBase& handle);

	/**
	 * @brief Unload the resource from the disk
	 *
	 * @param handle The handle of the resource
	 */
	void UnloadResource(const ResourceHandleBase& handle);

	/**
	 * @brief Reload the resource from the disk
	 *
	 * @param handle The handle of the resource
	 */
	void ReloadResource(const ResourceHandleBase& handle);

	/**
	 * @brief Unload all unused resources.
	 */
	void UnloadUnusedResources();

	/**
	 * @brief Get the loaded resource
	 *
	 * @param handle The handle of the resource
	 * @return std::shared_ptr<Resource> A shared pointer to the resource
	 */
	std::shared_ptr<Resource> GetLoadedResource(const ResourceHandleBase& handle);

	/**
	 * @brief Get the loaded resource of type T
	 *
	 * @tparam T The type of the resource
	 * @param handle The handle of the resource
	 * @return std::shared_ptr<T> A shared pointer to the resource
	 */
	template<class T>
		requires std::derived_from<T, Resource>
	std::shared_ptr<T> GetLoadedResource(const ResourceHandleBase& handle) {
		return std::static_pointer_cast<T>(GetLoadedResource(handle));
	}

  private:
	struct HandleData {
		HandleData(const fs::path& _path, MetaData&& _meta) : path(_path), meta(std::move(_meta)) {}
		fs::path path;
		MetaData meta;
	};
	std::size_t GetNextID() { return ++_nextID; }
	std::size_t GetID(const fs::path& path) const {
		auto iter = _pathToID.find(fs::absolute(_assetsPath / path));
		if (iter == _pathToID.end())
			return 0;
		else
			return iter->second;
	}

  private:
	std::size_t														 _nextID {0};
	std::unordered_map<std::string, std::unique_ptr<ResourceLoader>> _loaders;

	std::unordered_map<fs::path, std::size_t, Hasher<fs::path>> _pathToID;

	std::unordered_map<std::size_t, std::shared_ptr<Resource>>		 _cache;
	std::unordered_map<std::size_t, HandleData>						 _handles;
	std::unordered_map<std::size_t, std::filesystem::file_time_type> _watchedHandles;

	fs::path _assetsPath {"../Assets"};
};

/**
 * @brief A handle class with some convenient methods
 *
 * @tparam T Type of the resource
 */
template<class T>
	requires std::derived_from<T, Resource>
class ResourceHandle : public ResourceHandleBase {
	friend class ResourceManager;

  public:
	ResourceHandle() = default;
	void Load() const { _manager->LoadResource(*this); }
	void Reload() const { _manager->ReloadResource(*this); }
	void Unload() const { _manager->UnloadResource(*this); }
	void SetWatched(bool watched) const {
		if (watched)
			_manager->AddWatch(*this);
		else
			_manager->RemoveWatch(*this);
	}
	std::shared_ptr<T> operator*() const { return std::static_pointer_cast<T>(_manager->GetLoadedResource(*this)); }

  private:
	ResourceManager* _manager;
};

template<class T>
	requires std::derived_from<T, Resource>
ResourceHandle<T> ResourceManager::GetHandle(const fs::path& path) {
	ResourceHandle<T> handle;
	auto			  id = GetID(path);
	if (!id) {
		LOG_ERROR("Unknown resource path: {}", path.string());
	}
	handle.ID		= id;
	handle._manager = this;
	return handle;
}

} // namespace EngineS
