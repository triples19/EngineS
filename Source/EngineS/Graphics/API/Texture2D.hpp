#pragma once

#include "RenderTypes.hpp"
#include "Resource/Resource.hpp"

namespace EngineS {

struct SamplerDescriptor {
    SamplerFilter      magFilter {SamplerFilter::Linear};
    SamplerFilter      minFilter {SamplerFilter::Linear};
    SamplerAddressMode sAddressMode {SamplerAddressMode::ClampToEdge};
    SamplerAddressMode tAddressMode {SamplerAddressMode::ClampToEdge};
};

struct TextureDescriptor {
    TextureType       textureType {TextureType::Texture2D};
    PixelFormat       textureFormat {PixelFormat::RGBA8888};
    TextureUsage      textureUsage {TextureUsage::Read};
    u32               width {0};
    u32               height {0};
    u32               depth {0};
    SamplerDescriptor samplerDescriptor {};
    const byte*       data {nullptr};
};

class Texture2D : public Resource {
    ES_OBJECT
  public:
    virtual bool Load(const std::filesystem::path& path) override;

    virtual void Init(const TextureDescriptor& desc);
    virtual void UpdateData(const byte* data, u32 width, u32 height);
    virtual void Apply(u32 index) const = 0;

    u32 GetWidth() const { return _width; }
    u32 GetHeight() const { return _height; }

  private:
    u32         _width {0}, _height {0};
    PixelFormat _format;
};

} // namespace EngineS
