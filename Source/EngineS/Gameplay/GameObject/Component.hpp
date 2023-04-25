#pragma once

#include "Core/Object.hpp"

#include <vector>

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

    GameObject* GetGameObject() const { return _gameObject; }

    Component*              GetComponent(const Type* type) const;
    std::vector<Component*> GetComponents(const Type* type) const;

    template<class T>
    T* GetComponent() const;

    template<class T>
    std::vector<T*> GetComponents() const;

  private:
    bool        _enabled {true};
    GameObject* _gameObject {nullptr};
};

} // namespace EngineS

#include "GameObject.hpp"

namespace EngineS {

template<class T>
T* Component::GetComponent() const {
    return _gameObject->GetComponent<T>();
}

template<class T>
std::vector<T*> Component::GetComponents() const {
    return _gameObject->GetComponents<T>();
}

} // namespace EngineS