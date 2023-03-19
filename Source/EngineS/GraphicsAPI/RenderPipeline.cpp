#include "GraphicsAPI/RenderPipeline.hpp"

namespace EngineS {

RenderPipeline::RenderPipeline(const RenderPipelineDescriptor& desc) :
    _program(desc.program), _vertexLayout(desc.vertexLayout), _renderPrimitive(desc.renderPrimitive) {}

} // namespace EngineS
