#pragma once

#include <filesystem>
#include <memory>

namespace EngineS {

class GameObject;

class GameObjectFactory {
  public:
	static std::shared_ptr<GameObject> CreateSprite(std::filesystem::path path);
};

} // namespace EngineS
