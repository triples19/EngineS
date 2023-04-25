#pragma once

#include "Core/Macros.hpp"
#include "Graphics/API/RenderPipeline.hpp"
#include "Graphics/API/RenderTypes.hpp"

#include "glad/glad.h"

namespace EngineS {

class RenderPipelineOpenGL : public RenderPipeline {
    ES_OBJECT
  public:
    RenderPipelineOpenGL(const RenderPipelineDescriptor& desc);
};

} // namespace EngineS
