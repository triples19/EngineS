#pragma once

#include "GraphicsAPI/Texture2D.hpp"

#include "glad/glad.h"

namespace EngineS {

class Texture2DOpenGL : public Texture2D {
    ES_OBJECT
  public:
    ~Texture2DOpenGL();
    void Init(const TextureDescriptor& desc) override;
    void UpdateData(const byte* data, u32 width, u32 height) override;
    void Apply(u32 index) const override;

    GLuint GetHandler() const { return _texture; }

  private:
    GLuint _texture {0};
    GLint  _internalFormat;
    GLenum _dataType;
    GLuint _imageFormat;
    GLint  _wrapS, _wrapT;
    GLint  _minFilter, _magFilter;
};

} // namespace EngineS
