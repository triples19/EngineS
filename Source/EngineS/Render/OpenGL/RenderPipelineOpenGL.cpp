#include "Render/OpenGL/RenderPipelineOpenGL.hpp"
#include "Render/OpenGL/ProgramOpenGL.hpp"
#include "Render/OpenGL/UtilsOpenGL.hpp"

namespace EngineS {

RenderPipelineOpenGL::RenderPipelineOpenGL(const RenderPipelineDescriptor& desc) {
    _program         = static_cast<ProgramOpenGL*>(desc.program)->GetHandler();
    _vertexLayout    = desc.vertexLayout;
    _renderPrimitive = UtilsOpenGL::ConvertRenderPrimitive(desc.renderPrimitive);
}

} // namespace EngineS