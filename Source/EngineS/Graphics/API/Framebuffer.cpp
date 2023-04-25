#include "Framebuffer.hpp"

#include <algorithm>
#include <iterator>

namespace EngineS {

Framebuffer::Framebuffer(const FramebufferDescriptor& desc) {
    std::ranges::transform(
        desc.colorAttachments,
        std::back_inserter(_colorAttachments),
        [](const Attachment& attachment) { return attachment.texture; }
    );
    _depthAttachment = desc.depthAttachment.texture;
}

Texture2D* Framebuffer::GetColorAttachment(u32 index) const {
    return _colorAttachments[index];
}

Texture2D* Framebuffer::GetDepthAttachment() const {
    return _depthAttachment;
}

} // namespace EngineS
