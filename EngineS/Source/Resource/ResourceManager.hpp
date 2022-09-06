#pragma once

#include "Core/Base/Hash.hpp"
#include "Resource.hpp"

#include <filesystem>
#include <memory>
#include <string>
#include <unordered_map>

namespace fs = std::filesystem;

namespace EngineS {

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
	void AddWatch(ResourceHandle* handle);

	/**
	 * @brief Remove file modification watch for a handle
	 */
	void RemoveWatch(ResourceHandle* handle);

	/**
	 * @brief Get the ResourceHandle by path
	 *
	 * @param path The resource file path
	 * @return ResourceHandle* A weak pointer to the handle
	 */
	ResourceHandle* GetHandle(const fs::path& path);

	/**
	 * @brief Get the ResourceLoader by handle
	 *
	 * @param handle The resource handle
	 * @return ResourceLoader* A weak pointer to the loader
	 */
	ResourceLoader* GetLoader(ResourceHandle* handle);

	/**
	 * @brief Load the resource from the disk
	 *
	 * @param handle The handle of the resource
	 */
	void LoadResource(ResourceHandle* handle);

	/**
	 * @brief Unload the resource from the disk
	 *
	 * @param handle The handle of the resource
	 */
	void UnloadResource(ResourceHandle* handle);

	/**
	 * @brief Reload the resource from the disk
	 *
	 * @param handle The handle of the resource
	 */
	void ReloadResource(ResourceHandle* handle);

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
	std::shared_ptr<Resource> GetLoadedResource(ResourceHandle* handle);

	/**
	 * @brief Get the loaded resource of type T
	 *
	 * @tparam T The type of the resource
	 * @param handle The handle of the resource
	 * @return std::shared_ptr<T> A shared pointer to the resource
	 */
	template<class T>
	std::shared_ptr<T> GetLoadedResource(ResourceHandle* handle) {
		return std::static_pointer_cast<T>(GetLoadedResource(handle));
	}

  private:
	std::unordered_map<std::string, std::unique_ptr<ResourceLoader>>	 _loaders;
	std::unordered_map<ResourceHandle*, std::shared_ptr<Resource>>		 _cache;
	std::unordered_map<fs::path, std::unique_ptr<ResourceHandle>, Hasher<fs::path>>		 _handles;
	std::unordered_map<ResourceHandle*, std::filesystem::file_time_type> _watchedHandles;
};

} // namespace EngineS