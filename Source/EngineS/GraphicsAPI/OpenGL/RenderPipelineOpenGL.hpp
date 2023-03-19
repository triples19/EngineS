#pragma once

#include "Base/Macros.hpp"
#include "GraphicsAPI/RenderPipeline.hpp"
#include "GraphicsAPI/RenderTypes.hpp"

#include "glad/glad.h"

namespace EngineS {

class RenderPipelineOpenGL : public RenderPipeline {
    ES_OBJECT
  public:
    RenderPipelineOpenGL(const RenderPipelineDescriptor& desc);
};

} // namespace EngineS
