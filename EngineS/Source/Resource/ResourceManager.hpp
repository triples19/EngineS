#pragma once

#include <filesystem>
#include <fstream>
#include <memory>
#include <optional>
#include <sstream>
#include <string>

namespace fs = std::filesystem;

namespace EngineS {

class Shader;
class Texture2D;

class ResourceManager {
  public:
	void Initialize();

	std::stringstream LoadStringStream(fs::path path);
	std::string		  LoadText(fs::path path);
	std::shared_ptr<Shader>
	LoadShader(fs::path vertexPath, fs::path fragmentPath, std::optional<fs::path> geometryPath = std::nullopt);
	std::shared_ptr<Texture2D> LoadTexture2D(fs::path path, bool alpha);
};

} // namespace EngineS