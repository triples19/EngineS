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
};

} // namespace EngineS
