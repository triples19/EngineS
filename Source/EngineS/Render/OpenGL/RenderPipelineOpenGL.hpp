#pragma once

#include "Base/Macros.hpp"
#include "Render/RenderPipeline.hpp"
#include "Render/RenderTypes.hpp"

#include <glad/glad.h>

namespace EngineS {

class RenderPipelineOpenGL : public RenderPipeline {
    ES_OBJECT
  public:
    RenderPipelineOpenGL(const RenderPipelineDescriptor& desc);

    GLuint              GetProgram() const { return _program; }
    const VertexLayout& GetVertexLayout() const { return _vertexLayout; }
    GLenum              GetRenderPrimitive() const { return _renderPrimitive; }

  private:
    GLuint       _program;
    VertexLayout _vertexLayout;
    GLenum       _renderPrimitive;
};

} // namespace EngineS
