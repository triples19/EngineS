#include "Render/OpenGL/UtilsOpenGL.hpp"
#include "IO/Logger.hpp"

namespace EngineS {

bool UtilsOpenGL::CheckError() {
    GLenum error = glGetError();
    if (error) {
        Logger::Error("OpenGL error 0x{:04X}", error);
        return true;
    }
    return false;
}

void UtilsOpenGL::ConvertPixelFormat(PixelFormat pixelFormat, GLint& interalFormat, GLuint& format, GLenum& type) {
    switch (pixelFormat) {
        case PixelFormat::RGBA8888: {
            interalFormat = GL_RGBA;
            format        = GL_RGBA;
            type          = GL_UNSIGNED_BYTE;
            break;
        }
        case PixelFormat::RGB888: {
            interalFormat = GL_RGB;
            format        = GL_RGB;
            type          = GL_UNSIGNED_BYTE;
            break;
        }
        case PixelFormat::RGBA4444: {
            interalFormat = GL_RGBA;
            format        = GL_RGBA;
            type          = GL_UNSIGNED_SHORT_4_4_4_4;
            break;
        }
    }
}

GLint UtilsOpenGL::ConvertAddressMode(SamplerAddressMode addressMode) {
    switch (addressMode) {
        case SamplerAddressMode::Repeat:
            return GL_REPEAT;
        case SamplerAddressMode::MirrorRepeat:
            return GL_MIRRORED_REPEAT;
        case SamplerAddressMode::ClampToEdge:
            return GL_CLAMP_TO_EDGE;
        case SamplerAddressMode::DontCare:
            return GL_REPEAT;
    }
}

GLint UtilsOpenGL::ConvertFilter(SamplerFilter filter) {
    switch (filter) {
        case SamplerFilter::Linear:
            return GL_LINEAR;
        case SamplerFilter::LinearMipmapLinear:
            return GL_LINEAR_MIPMAP_LINEAR;
        case SamplerFilter::LinearMipmapNearest:
            return GL_LINEAR_MIPMAP_NEAREST;
        case SamplerFilter::Nearest:
            return GL_NEAREST;
        case SamplerFilter::NearestMipmapNearest:
            return GL_NEAREST_MIPMAP_NEAREST;
        case SamplerFilter::NearestMipmapLinear:
            return GL_NEAREST_MIPMAP_LINEAR;
        case SamplerFilter::DontCare:
            return GL_NEAREST;
    }
}

GLenum UtilsOpenGL::ConvertBufferType(BufferType type) {
    switch (type) {
        case BufferType::Vertex:
            return GL_ARRAY_BUFFER;
        case BufferType::Index:
            return GL_ELEMENT_ARRAY_BUFFER;
    }
}

GLenum UtilsOpenGL::ConvertBufferUsage(BufferUsage usage) {
    switch (usage) {
        case BufferUsage::Static:
            return GL_STATIC_DRAW;
        case BufferUsage::Dynamic:
            return GL_DYNAMIC_DRAW;
    }
}

GLenum UtilsOpenGL::ConvertShaderStage(ShaderStage stage) {
    switch (stage) {
        case ShaderStage::Vertex:
            return GL_VERTEX_SHADER;
        case ShaderStage::Fragment:
            return GL_FRAGMENT_SHADER;
    }
}

GLenum UtilsOpenGL::ConvertRenderPrimitive(RenderPrimitive renderPrimitive) {
    switch (renderPrimitive) {
        case RenderPrimitive::Point:
            return GL_POINT;
        case RenderPrimitive::Line:
            return GL_LINE;
        case RenderPrimitive::LineStrip:
            return GL_LINE_STRIP;
        case RenderPrimitive::Triangles:
            return GL_TRIANGLES;
        case RenderPrimitive::TrianglesStrip:
            return GL_TRIANGLE_STRIP;
    }
}

GLsizei UtilsOpenGL::ConvertAttributeSize(VertexFormat format) {
    switch (format) {
        case VertexFormat::Float4:
        case VertexFormat::Int4:
        case VertexFormat::UByte4:
        case VertexFormat::UShort4:
            return 4;
        case VertexFormat::Float3:
        case VertexFormat::Int3:
            return 3;
        case VertexFormat::Float2:
        case VertexFormat::Int2:
        case VertexFormat::UShort2:
            return 2;
        case VertexFormat::Float:
        case VertexFormat::Int:
            return 1;
    }
}

GLenum UtilsOpenGL::ConvertAttributeType(VertexFormat format) {
    switch (format) {
        case VertexFormat::Float4:
        case VertexFormat::Float3:
        case VertexFormat::Float2:
        case VertexFormat::Float:
            return GL_FLOAT;
        case VertexFormat::Int4:
        case VertexFormat::Int3:
        case VertexFormat::Int2:
        case VertexFormat::Int:
            return GL_INT;
        case VertexFormat::UShort4:
        case VertexFormat::UShort2:
            return GL_UNSIGNED_SHORT;
        case VertexFormat::UByte4:
            return GL_UNSIGNED_BYTE;
    }
}

} // namespace EngineS