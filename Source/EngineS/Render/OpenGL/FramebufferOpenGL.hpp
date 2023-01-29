#pragma once

#include "Render/Framebuffer.hpp"

#include <glad/glad.h>

namespace EngineS {

class FramebufferOpenGL : public Framebuffer {
    ES_OBJECT
  public:
    FramebufferOpenGL(const FramebufferDescriptor& desc);

    GLuint GetHandler() const { return _fbo; }

  private:
    GLuint _fbo;
};

} // namespace EngineS
