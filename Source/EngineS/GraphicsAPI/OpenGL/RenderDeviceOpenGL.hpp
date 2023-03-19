#pragma once

#include "GraphicsAPI/RenderDevice.hpp"

namespace EngineS {

class RenderDeviceOpenGL : public RenderDevice {
  public:
    RenderDeviceOpenGL();
    ~RenderDeviceOpenGL();

    Shader*     CreateShader() override;
    const Type* GetShaderType() override;

    Program*    CreateProgram() override;
    const Type* GetProgramType() override;

    Buffer*     CreateBuffer(std::size_t size, BufferType type, BufferUsage usage) override;
    const Type* GetBufferType() override;

    Texture2D*  CreateTexture2D() override;
    const Type* GetTexture2DType() override;

    DrawList*   CreateDrawList() override;
    const Type* GetDrawListType() override;

    RenderPipeline* CreateRenderPipeline(const RenderPipelineDescriptor& desc) override;
    const Type*     GetRenderPipelineType() override;

    Framebuffer* CreateFramebuffer(const FramebufferDescriptor& desc) override;
    const Type*  GetFramebufferType() override;
};

} // namespace EngineS
