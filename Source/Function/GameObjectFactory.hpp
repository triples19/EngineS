#pragma once

#include <filesystem>
#include <memory>

namespace EngineS {

class GameObject;

class GameObjectFactory {
  public:
    static GameObject* CreateGameObject();
    static GameObject* CreateSprite(std::filesystem::path path);
    static GameObject* CreateCamera();
};

} // namespace EngineS
