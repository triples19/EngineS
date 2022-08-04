#include "ResourceManager.hpp"

#include "Core/Base/Macros.hpp"
#include "Function/Render/Shader.hpp"
#include "Function/Render/Texture2D.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

namespace EngineS {

void ResourceManager::Initialize() {
	stbi_set_flip_vertically_on_load(true);
}

void ResourceManager::LoadDefaultResources() {
	_defaultResource.defaultSpriteShader = LoadShader("Assets/vertex.glsl", "Assets/fragment.glsl");
}

std::stringstream ResourceManager::LoadStringStream(fs::path path) {
	if (!exists(path)) {
		LOG_ERROR("File {} does not exist.", path.string());
		return {};
	}
	std::ifstream	  file(path);
	std::stringstream ss;
	ss << file.rdbuf();
	return ss;
}

std::string ResourceManager::LoadText(fs::path path) {
	return LoadStringStream(path).str();
}

std::shared_ptr<Shader>
ResourceManager::LoadShader(fs::path vertexPath, fs::path fragmentPath, std::optional<fs::path> geometryPath) {
	auto vertexSource	= LoadText(vertexPath);
	auto fragmentSource = LoadText(fragmentPath);
	auto geometrySource = geometryPath ? std::optional<std::string>(LoadText(*geometryPath)) : std::nullopt;
	auto shader			= std::make_shared<Shader>();
	shader->Compile(vertexSource, fragmentSource, geometrySource);
	return shader;
}

std::shared_ptr<Texture2D> ResourceManager::LoadTexture2D(fs::path path) {
	if (!exists(path)) {
		LOG_ERROR("File {} does not exist.", path.string());
		return nullptr;
	}
	auto  texture = std::make_shared<Texture2D>();
	int	  width, height, nrChannels;
	auto* data = stbi_load(path.string().c_str(), &width, &height, &nrChannels, 0);
	if (!data) {
		LOG_ERROR("Failed to load image {}", path.string());
		return nullptr;
	}
	if (nrChannels == 4) {
		texture->internalFormat = GL_RGBA;
		texture->imageFormat	= GL_RGBA;
	}
	texture->Generate(width, height, data);
	stbi_image_free(data);
	return texture;
}
std::shared_ptr<Shader> ResourceManager::GetDefaultSpriteShader() const {
	return _defaultResource.defaultSpriteShader;
}

} // namespace EngineS
