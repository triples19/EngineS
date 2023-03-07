#pragma once

#include "Render/RenderTypes.hpp"

#ifdef REFL_COMPILER
#define __cpp_consteval
#endif

#include <glad/glad.h>
#include <source_location>

namespace EngineS {

class UtilsOpenGL {
  public:
    static bool CheckError(const std::source_location& loc = std::source_location::current());

    static void ConvertPixelFormat(PixelFormat pixelFormat, GLint& interalFormat, GLuint& format, GLenum& type);

    static GLint   ConvertAddressMode(SamplerAddressMode addressMode);
    static GLint   ConvertFilter(SamplerFilter filter);
    static GLenum  ConvertBufferType(BufferType type);
    static GLenum  ConvertBufferUsage(BufferUsage usage);
    static GLenum  ConvertShaderStage(ShaderStage stage);
    static GLenum  ConvertRenderPrimitive(RenderPrimitive renderPrimitive);
    static GLsizei ConvertAttributeSize(VertexFormat format);
    static GLenum  ConvertAttributeType(VertexFormat format);
};

} // namespace EngineS
