#pragma once

#include "Core/Base/Object.hpp"
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
class ResourceHandle : public Object {
	friend class ResourceManager;

  public:
	ResourceHandle(std::shared_ptr<MetaData> metaData, const fs::path& resourcePath) :
		_meta {metaData}, _path {resourcePath} {}
	virtual ~ResourceHandle() = default;

	const MetaData& GetMetaData() const { return *_meta; }
	const fs::path& GetPath() const { return _path; }

  private:
	fs::path				  _path;
	std::size_t				  _id;
	std::shared_ptr<MetaData> _meta;
};

/**
 * @brief A facotry class for creating and reloading the resource.
 *
 */
class ResourceLoader : public Object {
  public:
	virtual Resource* CreateResource(const fs::path& path) const = 0;
	virtual void	  ReloadResource(std::shared_ptr<Resource>& resource, const fs::path& path) {
			 resource.reset(CreateResource(path));
	}
	virtual std::string GetName() const = 0;

  protected:
	std::string ReadString(const fs::path& path) const {
		std::ifstream	  file(path);
		std::stringstream ss;
		ss << file.rdbuf();
		return ss.str();
	}
};

} // namespace EngineS