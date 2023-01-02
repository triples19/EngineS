#include "Texture2D.hpp"

#include "Base/Macros.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace EngineS {

bool Texture2D::Load(const std::filesystem::path& path) {
    int  width, height, nrChannels;
    auto data = stbi_load(path.string().c_str(), &width, &height, &nrChannels, 0);
    if (!data) {
        LOG_ERROR("Failed to load image");
        return false;
    }
    if (nrChannels == 4) {
        _internalFormat = GL_RGBA;
        _imageFormat    = GL_RGBA;
    }
    Generate(width, height, data);
    stbi_image_free(data);
    return true;
}

void Texture2D::Generate(unsigned int width, unsigned int height, unsigned char* data) {
    this->_width  = width;
    this->_height = height;

    glGenTextures(1, &_id);
    glBindTexture(GL_TEXTURE_2D, _id);
    glTexImage2D(GL_TEXTURE_2D, 0, _internalFormat, width, height, 0, _imageFormat, GL_UNSIGNED_BYTE, data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, _wrapS);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, _wrapT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, _filterMin);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, _filterMax);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture2D::Bind() const {
    glBindTexture(GL_TEXTURE_2D, _id);
}

} // namespace EngineS