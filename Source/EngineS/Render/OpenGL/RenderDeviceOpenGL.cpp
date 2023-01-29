#include "Render/OpenGL/RenderDeviceOpenGL.hpp"
#include "Render/OpenGL/BufferOpenGL.hpp"
#include "Render/OpenGL/DrawListOpenGL.hpp"
#include "Render/OpenGL/FramebufferOpenGL.hpp"
#include "Render/OpenGL/ProgramOpenGL.hpp"
#include "Render/OpenGL/RenderPipelineOpenGL.hpp"
#include "Render/OpenGL/ShaderOpenGL.hpp"
#include "Render/OpenGL/Texture2DOpenGL.hpp"

#include <GLFW/glfw3.h>

namespace EngineS {

RenderDeviceOpenGL::RenderDeviceOpenGL() {
    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
        Logger::Error("Failed to initialize GLAD");
        return;
    }

    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
}

RenderDeviceOpenGL::~RenderDeviceOpenGL() = default;

Shader* RenderDeviceOpenGL::CreateShader() {
    return new ShaderOpenGL();
}

const Type* RenderDeviceOpenGL::GetShaderType() {
    return ShaderOpenGL::GetTypeStatic();
}

Program* RenderDeviceOpenGL::CreateProgram() {
    return new ProgramOpenGL();
}

const Type* RenderDeviceOpenGL::GetProgramType() {
    return ProgramOpenGL::GetTypeStatic();
}

Buffer* RenderDeviceOpenGL::CreateBuffer(std::size_t size, BufferType type, BufferUsage usage) {
    return new BufferOpenGL(size, type, usage);
}

const Type* RenderDeviceOpenGL::GetBufferType() {
    return BufferOpenGL::GetTypeStatic();
}

Texture2D* RenderDeviceOpenGL::CreateTexture2D() {
    return new Texture2DOpenGL();
}

const Type* RenderDeviceOpenGL::GetTexture2DType() {
    return Texture2DOpenGL::GetTypeStatic();
}

DrawList* RenderDeviceOpenGL::CreateDrawList() {
    return new DrawListOpenGL();
}

const Type* RenderDeviceOpenGL::GetDrawListType() {
    return DrawListOpenGL::GetTypeStatic();
}

RenderPipeline* RenderDeviceOpenGL::CreateRenderPipeline(const RenderPipelineDescriptor& desc) {
    return new RenderPipelineOpenGL(desc);
}

const Type* RenderDeviceOpenGL::GetRenderPipelineType() {
    return RenderPipelineOpenGL::GetTypeStatic();
}

Framebuffer* RenderDeviceOpenGL::CreateFramebuffer(const FramebufferDescriptor& desc) {
    return new FramebufferOpenGL(desc);
}

const Type* RenderDeviceOpenGL::GetFramebufferType() {
    return FramebufferOpenGL::GetTypeStatic();
}

} // namespace EngineS