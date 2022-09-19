#pragma once

#include <memory>
#include <unordered_set>
#include <vector>

namespace EngineS {

class GameObject;
class Camera;
class Transform2D;

class Scene {
  public:
	Scene();
	~Scene();

	virtual void Initialize();

	auto&		 GetGameObjects() { return _gameObjects; }
	void		 AddGameObject(std::shared_ptr<GameObject> gameObject);
	void		 AddGameObject(std::shared_ptr<GameObject> gameObject, Transform2D* parent);
	Camera*		 GetMainCamera() { return _mainCamera; }
	Transform2D* GetRootTransform();

  private:
	std::unordered_set<std::shared_ptr<GameObject>> _gameObjects;
	Camera*											_mainCamera;
	std::shared_ptr<GameObject>						_rootGameObject;
};

} // namespace EngineS
