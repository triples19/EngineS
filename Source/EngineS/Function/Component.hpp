#pragma once

#include "Base/Object.hpp"

namespace EngineS {

class GameObject;
class Transform2D;
class Renderer;

class Component : public Object {
    ES_OBJECT
  public:
    virtual void Initialize(GameObject* parent);
    virtual void Update(float deltaTime) {}

    void SetEnabled(bool value) { _enabled = value; }
    bool GetEnabled() const { return _enabled; }

    GameObject*  GetGameObject() const { return _gameObject; }
    Transform2D* GetTransform() const { return _transform; }
    Renderer*    GetRenderer() const { return _renderer; }

  private:
    bool         _enabled {true};
    GameObject*  _gameObject {nullptr};
    Transform2D* _transform {nullptr};
    Renderer*    _renderer {nullptr};
};

} // namespace EngineS
