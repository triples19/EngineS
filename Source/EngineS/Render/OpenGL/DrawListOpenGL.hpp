#pragma once

#include "Render/DrawList.hpp"

namespace EngineS {

class RenderPipelineOpenGL;

class DrawListOpenGL : public DrawList {
    ES_OBJECT
  public:
    void Begin() override;
    void BindRenderPipeline(const RenderPipeline* pipeline) override;
    void BindVertexBuffer(const Buffer* buffer) override;
    void BindTexture(const Texture2D* texture) override;
    void Draw(std::size_t start, std::size_t count) override;
    void End() override;

  private:
    const RenderPipelineOpenGL* _pipeline;
};

} // namespace EngineS
