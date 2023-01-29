#pragma once

#include "Base/PrimitiveTypes.hpp"

#include <vector>

namespace EngineS {

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
    D16,
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

} // namespace EngineS