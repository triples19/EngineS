#include "Texture2D.hpp"

#include "Core/Base/Macros.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

namespace EngineS {

void Texture2D::Generate(unsigned int width, unsigned int height, unsigned char* data) {
	this->width	 = width;
	this->height = height;

	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);
	glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, imageFormat, GL_UNSIGNED_BYTE, data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapS);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filterMin);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filterMax);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture2D::Bind() const {
	glBindTexture(GL_TEXTURE_2D, id);
}

Resource* Texture2DLoader::CreateResource(const fs::path& path) const {
	stbi_set_flip_vertically_on_load(true);
	auto texture = new Texture2D;
	int	 width, height, nrChannels;
	auto data = stbi_load(path.string().c_str(), &width, &height, &nrChannels, 0);
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

} // namespace EngineS