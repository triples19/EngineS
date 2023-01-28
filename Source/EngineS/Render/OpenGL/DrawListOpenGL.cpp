#include "Render/OpenGL/DrawListOpenGL.hpp"
#include "Render/OpenGL/BufferOpenGL.hpp"
#include "Render/OpenGL/RenderPipelineOpenGL.hpp"
#include "Render/OpenGL/Texture2DOpenGL.hpp"
#include "Render/OpenGL/UtilsOpenGL.hpp"

namespace EngineS {

void DrawListOpenGL::Begin() {}

void DrawListOpenGL::BindRenderPipeline(const RenderPipeline* pipeline) {
    _pipeline = static_cast<const RenderPipelineOpenGL*>(pipeline);

    glUseProgram(_pipeline->GetProgram());
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
    glDrawArrays(_pipeline->GetRenderPrimitive(), start, count);
    UtilsOpenGL::CheckError();
}

void DrawListOpenGL::End() {}

} // namespace EngineS