#pragma once

#include "Base/Object.hpp"
#include "GraphicsAPI/DeviceInfo.hpp"

#include <memory>
#include <utility>

namespace EngineS {

class Material2D;
class Transform2D;
class Program;
class Texture2D;
class DeviceInfo;
class Framebuffer;

class RenderSystem : public Object {
    ES_OBJECT
  public:
    static RenderSystem* Instance();

    RenderSystem();
    ~RenderSystem();

    void Initialize();

    void Update();

  private:
    void OnWindowSizeChange(u32 width, u32 height);

  private:
    DeviceInfo   _deviceInfo;
    Framebuffer* _framebuffer {nullptr};
    Texture2D*   _colorTex {nullptr};
    Texture2D*   _depthTex {nullptr};
};

} // namespace EngineS
