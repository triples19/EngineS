#pragma once

#include "Math/Color.hpp"
#include "Render/DrawList.hpp"

namespace EngineS {

class RenderPipelineOpenGL;
class FramebufferOpenGL;

class DrawListOpenGL : public DrawList {
    ES_OBJECT
  public:
    void Begin(const RenderPassDescriptor& desc) override;
    void SetViewport(i32 x, i32 y, u32 w, u32 h) override;
    void BindRenderPipeline(const RenderPipeline* pipeline) override;
    void BindVertexBuffer(const Buffer* buffer) override;
    void BindTexture(const Texture2D* texture) override;
    void Draw(std::size_t start, std::size_t count) override;
    void End() override;

  private:
    const RenderPipelineOpenGL* _pipeline;
    FramebufferOpenGL*          _framebuffer;
};

} // namespace EngineS
