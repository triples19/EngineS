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

    // void AddToBatch(
    //     std::shared_ptr<Material2D> material,
    //     const Matrix4x4&            modelMat,
    //     const Vector2&              anchor,
    //     const Color4F&              color
    // );

    // std::shared_ptr<Material2D>
    // GetOrCreateMaterial(std::shared_ptr<Program> program, std::shared_ptr<Texture2D> texture);

  private:
    GLFWwindow* _window;
    DeviceInfo  _deviceInfo;

    // std::unordered_map<std::size_t, std::shared_ptr<Material2D>> _materials;
    // std::unordered_map<unsigned int, SpriteBatch>                _batches;
};

} // namespace EngineS
