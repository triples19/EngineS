#pragma once

#include "GraphicsAPI/Shader.hpp"

#include "glad/glad.h"

namespace EngineS {

class ShaderOpenGL : public Shader {
    ES_OBJECT
  public:
    virtual ~ShaderOpenGL();

    GLuint GetHandler() const { return _shader; }

  protected:
    virtual bool CompileInternal(ShaderStage stage, const char** src, std::size_t size) override;

  private:
    GLuint _shader {0};
};

} // namespace EngineS
