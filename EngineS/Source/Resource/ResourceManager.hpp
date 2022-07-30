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
	static std::stringstream LoadStringStream(fs::path path);
	static std::string		 LoadText(fs::path path);
	static std::shared_ptr<Shader>
	LoadShader(fs::path vertexPath, fs::path fragmentPath, std::optional<fs::path> geometryPath = std::nullopt);
	static std::shared_ptr<Texture2D> LoadTexture2D(fs::path path, bool alpha);
};

} // namespace EngineS