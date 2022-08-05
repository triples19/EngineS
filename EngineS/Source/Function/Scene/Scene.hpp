#pragma once

#include <memory>
#include <vector>

namespace EngineS {

class GameObject;
class Camera;

class Scene {
  public:
	virtual void Initialize();

	auto&	GetGameObjects() { return _gameObjects; }
	void	AddGameObject(std::shared_ptr<GameObject> gameObject) { _gameObjects.push_back(gameObject); }
	Camera* GetMainCamera() { return _mainCamera; }

  private:
	std::vector<std::shared_ptr<GameObject>> _gameObjects;
	Camera*									 _mainCamera;
};

} // namespace EngineS
