#pragma once

#include "Render/Program.hpp"

#include <glad/glad.h>

namespace EngineS {

class ProgramOpenGL : public Program {
    ES_OBJECT
  public:
    ProgramOpenGL();
    ~ProgramOpenGL();

    bool Link(Shader* fragShader, Shader* vertShader) override;

    GLuint GetHandler() const { return _program; }

  private:
    GLuint _program;
};

} // namespace EngineS
