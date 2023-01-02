#pragma once

#include "Base/Object.hpp"

#include <memory>
#include <unordered_set>
#include <vector>

namespace EngineS {

class GameObject;
class Camera;
class Transform2D;

class Scene : public Object {
    ES_OBJECT
  public:
    Scene();
    virtual ~Scene();

    virtual void Initialize();

    auto&        GetGameObjects() { return _gameObjects; }
    void         AddGameObject(GameObject* gameObject);
    void         AddGameObject(GameObject* gameObject, Transform2D* parent);
    void         RemoveGameObject(GameObject* gameObject);
    Camera*      GetMainCamera() { return _mainCamera; }
    Transform2D* GetRootTransform();

  private:
    std::unordered_set<GameObject*> _gameObjects;
    Camera*                         _mainCamera;
    GameObject*                     _rootGameObject;
};

} // namespace EngineS
