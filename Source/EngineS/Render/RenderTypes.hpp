#pragma once

#include "Base/PrimitiveTypes.hpp"

#include <vector>

namespace EngineS {

class Program;
class Buffer;

enum class BufferUsage : u32 {
    Static,
    Dynamic,
};

enum class BufferType : u32 {
    Vertex,
    Index,
};

enum class VertexFormat : u32 {
    Float4,
    Float3,
    Float2,
    Float,
    Int4,
    Int3,
    Int2,
    Int,
    UShort4,
    UShort2,
    UByte4,
};

enum class ShaderStage : u32 {
    Vertex,
    Fragment,
};

enum class BlendOp : u32 {
    Add,
    Subtract,
};

enum class PixelFormat : u32 {
    RGBA8888,
    RGB888,
    RGBA4444,
};

enum class TextureType : u32 {
    Texture2D,
    TextureCube,
};

enum class TextureUsage : u32 {
    Read,
    Write,
    RenderTarget,
};

enum class SamplerFilter : u32 {
    Nearest,
    NearestMipmapNearest,
    NearestMipmapLinear,
    Linear,
    LinearMipmapLinear,
    LinearMipmapNearest,
    DontCare,
};

enum class SamplerAddressMode : u32 {
    Repeat,
    MirrorRepeat,
    ClampToEdge,
    DontCare,
};

enum class RenderPrimitive : u32 {
    Point,
    Line,
    LineStrip,
    Triangles,
    TrianglesStrip,
};

enum class CullMode : u32 {
    None,
    Back,
    Front,
};

enum class FrontFace : u32 {
    Clockwise,
    CounterClockwise,
};

struct SamplerDescriptor {
    SamplerFilter      magFilter {SamplerFilter::Linear};
    SamplerFilter      minFilter {SamplerFilter::Linear};
    SamplerAddressMode sAddressMode {SamplerAddressMode::ClampToEdge};
    SamplerAddressMode tAddressMode {SamplerAddressMode::ClampToEdge};
};

struct TextureDescriptor {
    TextureType       textureType {TextureType::Texture2D};
    PixelFormat       textureFormat {PixelFormat::RGBA8888};
    TextureUsage      textureUsage {TextureUsage::Read};
    u32               width {0};
    u32               height {0};
    u32               depth {0};
    SamplerDescriptor samplerDescriptor {};
};

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

} // namespace EngineS