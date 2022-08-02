#pragma once

#include <any>
#include <filesystem>
#include <fstream>
#include <memory>
#include <optional>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

namespace fs = std::filesystem;

namespace EngineS {

class Shader;
class Texture2D;

class ResourceManager {
  public:
	void Initialize();
	void LoadDefaultResources();

	std::shared_ptr<Shader>
	LoadShader(fs::path vertexPath, fs::path fragmentPath, std::optional<fs::path> geometryPath = std::nullopt);
	std::shared_ptr<Texture2D> LoadTexture2D(fs::path path);

	std::shared_ptr<Shader> GetDefaultSpriteShader() const;

  private:
	std::stringstream LoadStringStream(fs::path path);
	std::string		  LoadText(fs::path path);

  private:
	struct DefaultResource {
		std::shared_ptr<Shader> defaultSpriteShader;
	} _defaultResource;
};

} // namespace EngineS