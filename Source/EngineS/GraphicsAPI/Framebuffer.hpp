#pragma once

#include "Base/Object.hpp"

#include <vector>

namespace EngineS {

class Texture2D;

struct Attachment {
    Texture2D* texture {nullptr};
    u32        mipLevel {0};
    u32        layer {0};
};

struct FramebufferDescriptor {
    std::vector<Attachment> colorAttachments;
    bool                    hasDepthAttachment {false};
    Attachment              depthAttachment;
};

class Framebuffer : public Object {
    ES_OBJECT
  public:
    Framebuffer(const FramebufferDescriptor& desc);
    Texture2D* GetColorAttachment(u32 index) const;
    Texture2D* GetDepthAttachment() const;

  protected:
    std::vector<Texture2D*> _colorAttachments;
    Texture2D*              _depthAttachment;
};

} // namespace EngineS
