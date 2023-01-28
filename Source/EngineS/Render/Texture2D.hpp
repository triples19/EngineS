#pragma once

#include "Render/RenderTypes.hpp"
#include "Resource/Resource.hpp"

namespace EngineS {

class Texture2D : public Resource {
    ES_OBJECT
  public:
    virtual bool Load(const std::filesystem::path& path) override;

    virtual void Init(const TextureDescriptor& desc) = 0;
    virtual void UpdateData(const byte* data)        = 0;
    virtual void Apply(u32 index) const              = 0;

    u32 GetWidth() const { return _width; }
    u32 GetHeight() const { return _height; }

  private:
    u32         _width {0}, _height {0};
    PixelFormat _format;
};

} // namespace EngineS
