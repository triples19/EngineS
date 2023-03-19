#pragma once

#include "Base/Macros.hpp"
#include "GraphicsAPI/RenderTypes.hpp"

namespace EngineS {

class Program;

struct VertexAttribute {
    u32          location;
    u32          offset;
    VertexFormat format;
    bool         normalized {false};
};

struct VertexLayout {
    std::vector<VertexAttribute> attributes {};
    size_t                       stride {0};
};

struct RenderPipelineRasterizationState {
    bool      wireframe {false};
    CullMode  cullMode {CullMode::Back};
    FrontFace frontFace {FrontFace::CounterClockwise};
    float     lineWidth {1.0};
};

struct RenderPipelineDescriptor {
    Program*                         program;
    VertexLayout                     vertexLayout;
    RenderPrimitive                  renderPrimitive;
    RenderPipelineRasterizationState rasterizationState;
};

class RenderPipeline : public Object {
    ES_OBJECT
  public:
    RenderPipeline(const RenderPipelineDescriptor& desc);

    Program* GetProgram() const { return _program; }
    void     SetProgram(Program* p) { _program = p; }

    const VertexLayout& GetVertexLayout() const { return _vertexLayout; }

    RenderPrimitive GetRenderPrimitive() const { return _renderPrimitive; }

  private:
    Program*        _program;
    VertexLayout    _vertexLayout;
    RenderPrimitive _renderPrimitive;
};

} // namespace EngineS
