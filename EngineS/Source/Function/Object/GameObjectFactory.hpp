#pragma once

#include <filesystem>
#include <memory>

namespace EngineS {

class GameObject;

class GameObjectFactory {
  public:
	static std::shared_ptr<GameObject> CreateGameObject();
	static std::shared_ptr<GameObject> CreateSprite(std::filesystem::path path);
	static std::shared_ptr<GameObject> CreateCamera();
};

} // namespace EngineS
