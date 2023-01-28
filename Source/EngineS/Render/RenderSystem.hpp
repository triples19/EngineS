#pragma once

#include "Platform/GLCommon.hpp"
#include "Render/DeviceInfo.hpp"
#include "Render/Program.hpp"
#include "Render/SpriteBatch.hpp"
#include "Resource/ResourceManager.hpp"

#include <GLFW/glfw3.h>
#include <memory>
#include <utility>

namespace EngineS {

class Material2D;
class Transform2D;
class Program;
class Texture2D;
class DeviceInfo;

class RenderSystem : public Object {
    ES_OBJECT
  public:
    static RenderSystem* Instance();

    RenderSystem();
    ~RenderSystem();

    /**
     * Called after glfw window is initialized
     */
    void Initialize();

    void Update();

  private:
    GLFWwindow* _window;
    DeviceInfo  _deviceInfo;
};

} // namespace EngineS
