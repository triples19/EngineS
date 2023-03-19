#include "GraphicsAPI/OpenGL/FramebufferOpenGL.hpp"
#include "GraphicsAPI/OpenGL/Texture2DOpenGL.hpp"
#include "GraphicsAPI/OpenGL/UtilsOpenGL.hpp"

namespace EngineS {

FramebufferOpenGL::FramebufferOpenGL(const FramebufferDescriptor& desc) : Framebuffer(desc) {
    glGenFramebuffers(1, &_fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, _fbo);
    UtilsOpenGL::CheckError();

    for (int i = 0; i < desc.colorAttachments.size(); i++) {
        const auto& attachment = desc.colorAttachments[i];
        glFramebufferTexture2D(
            GL_FRAMEBUFFER,
            GL_COLOR_ATTACHMENT0 + i,
            GL_TEXTURE_2D,
            static_cast<Texture2DOpenGL*>(attachment.texture)->GetHandler(),
            attachment.mipLevel
        );
        UtilsOpenGL::CheckError();
    }

    if (desc.hasDepthAttachment) {
        glFramebufferTexture2D(
            GL_FRAMEBUFFER,
            GL_DEPTH_ATTACHMENT,
            GL_TEXTURE_2D,
            static_cast<Texture2DOpenGL*>(desc.depthAttachment.texture)->GetHandler(),
            desc.depthAttachment.mipLevel
        );
        UtilsOpenGL::CheckError();
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

} // namespace EngineS
