#pragma once

#include <memory>
#include <vector>

namespace EngineS {

class GameObject;

class Scene {
  public:
	virtual void Initialize() {}

	std::vector<std::shared_ptr<GameObject>>& GetGameObjects() { return _gameObjects; }
	void AddGameObject(std::shared_ptr<GameObject> gameObject) { _gameObjects.push_back(gameObject); }

  private:
	std::vector<std::shared_ptr<GameObject>> _gameObjects;
};

} // namespace EngineS
