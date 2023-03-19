#include "GraphicsAPI/OpenGL/DrawListOpenGL.hpp"
#include "GraphicsAPI/OpenGL/BufferOpenGL.hpp"
#include "GraphicsAPI/OpenGL/FramebufferOpenGL.hpp"
#include "GraphicsAPI/OpenGL/ProgramOpenGL.hpp"
#include "GraphicsAPI/OpenGL/RenderPipelineOpenGL.hpp"
#include "GraphicsAPI/OpenGL/Texture2DOpenGL.hpp"
#include "GraphicsAPI/OpenGL/UtilsOpenGL.hpp"

namespace EngineS {

void DrawListOpenGL::Begin(const RenderPassDescriptor& desc) {
    _framebuffer = static_cast<FramebufferOpenGL*>(desc.framebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, _framebuffer->GetHandler());

    GLbitfield clearMask = 0;
    if (desc.clearColor) {
        auto [r, g, b, a] = desc.clearColorValue.Values();
        glClearColor(r, g, b, a);
        clearMask |= GL_COLOR_BUFFER_BIT;
    }
    if (desc.clearDepth) {
        glClearDepth(desc.clearDepthValue);
        clearMask |= GL_DEPTH_BUFFER_BIT;
    }
    if (clearMask)
        glClear(clearMask);
    UtilsOpenGL::CheckError();
}

void DrawListOpenGL::SetViewport(i32 x, i32 y, u32 w, u32 h) {
    glViewport(x, y, w, h);
}

void DrawListOpenGL::BindRenderPipeline(const RenderPipeline* pipeline) {
    _pipeline = static_cast<const RenderPipelineOpenGL*>(pipeline);

    auto programGL = static_cast<const ProgramOpenGL*>(_pipeline->GetProgram());
    glUseProgram(programGL->GetHandler());

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    UtilsOpenGL::CheckError();
}

void DrawListOpenGL::BindTexture(const Texture2D* texture) {
    auto textureGL = static_cast<const Texture2DOpenGL*>(texture);
    textureGL->Apply(0);
    UtilsOpenGL::CheckError();
}

void DrawListOpenGL::BindVertexBuffer(const Buffer* buffer) {
    auto bufferGL = static_cast<const BufferOpenGL*>(buffer);

    glBindBuffer(GL_ARRAY_BUFFER, bufferGL->GetHandler());

    const auto& attributes = _pipeline->GetVertexLayout().attributes;
    for (const auto& attr : attributes) {
        glEnableVertexAttribArray(attr.location);
        glVertexAttribPointer(
            attr.location,
            UtilsOpenGL::ConvertAttributeSize(attr.format),
            UtilsOpenGL::ConvertAttributeType(attr.format),
            attr.normalized,
            _pipeline->GetVertexLayout().stride,
            reinterpret_cast<GLvoid*>(attr.offset)
        );
        UtilsOpenGL::CheckError();
    }
}

void DrawListOpenGL::Draw(std::size_t start, std::size_t count) {
    glDrawArrays(UtilsOpenGL::ConvertRenderPrimitive(_pipeline->GetRenderPrimitive()), start, count);
    UtilsOpenGL::CheckError();
}

void DrawListOpenGL::End() {
    glBindFramebuffer(GL_READ_FRAMEBUFFER, _framebuffer->GetHandler());
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
    auto width  = _framebuffer->GetColorAttachment(0)->GetWidth();
    auto height = _framebuffer->GetColorAttachment(0)->GetHeight();
    glBlitFramebuffer(0, 0, width, height, 0, 0, width, height, GL_COLOR_BUFFER_BIT, GL_NEAREST);
}

} // namespace EngineS
