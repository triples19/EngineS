#pragma once

#include "Core/Reflection/Type.hpp"
#include "RenderTypes.hpp"

namespace EngineS {

class Shader;
class Program;
class Buffer;
class Texture2D;
struct TextureDescriptor;
class DrawList;
class RenderPipeline;
struct RenderPipelineDescriptor;
class Framebuffer;
struct FramebufferDescriptor;

class RenderDevice {
  public:
    static RenderDevice* Instance();

    virtual ~RenderDevice() = default;

    virtual Shader*     CreateShader()  = 0;
    virtual const Type* GetShaderType() = 0;

    virtual Program*    CreateProgram()  = 0;
    virtual const Type* GetProgramType() = 0;

    virtual Buffer*     CreateBuffer(std::size_t size, BufferType type, BufferUsage usage) = 0;
    virtual const Type* GetBufferType()                                                    = 0;

    virtual Texture2D*  CreateTexture2D()  = 0;
    virtual const Type* GetTexture2DType() = 0;

    virtual DrawList*   CreateDrawList()  = 0;
    virtual const Type* GetDrawListType() = 0;

    virtual RenderPipeline* CreateRenderPipeline(const RenderPipelineDescriptor& desc) = 0;
    virtual const Type*     GetRenderPipelineType()                                    = 0;

    virtual Framebuffer* CreateFramebuffer(const FramebufferDescriptor& desc) = 0;
    virtual const Type*  GetFramebufferType()                                 = 0;
};

} // namespace EngineS
