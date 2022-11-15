#pragma once

#include "Platform/GLCommon.hpp"
#include "Resource/Resource.hpp"

namespace EngineS {

class Texture2D : public Resource {
    friend class Texture2DLoader;

  public:
    Texture2D() = default;

    void Generate(unsigned int width, unsigned int height, unsigned char* data);

    void Bind() const;

    unsigned int GetID() const { return _id; }
    unsigned int GetWidth() const { return _width; }
    unsigned int GetHeight() const { return _height; }

  private:
    unsigned int _id {0};
    unsigned int _width {0}, _height {0};
    unsigned int _internalFormat {GL_RGB};
    unsigned int _imageFormat {GL_RGB};
    unsigned int _wrapS {GL_REPEAT}, _wrapT {GL_REPEAT};
    unsigned int _filterMin {GL_LINEAR}, _filterMax {GL_LINEAR};
};

class Texture2DLoader : public ResourceLoader {
  public:
    virtual Resource*   CreateResource(const fs::path& path) const;
    virtual std::string GetName() const { return "Texture2DLoader"; }
};

} // namespace EngineS
