#pragma once

#include "Base/Object.hpp"

#include <vector>

namespace EngineS {

class Component;
class Renderer;
class Transform2D;

class GameObject : public Object {
    ES_OBJECT
  public:
    GameObject() = default;
    ~GameObject();
    virtual void Update(float deltaTime);

    Component*              AddComponent(const Type* type);
    Component*              GetComponent(const Type* type) const;
    std::vector<Component*> GetComponents(const Type* type) const;

    template<class T>
    T* AddComponent() {
        return static_cast<T*>(AddComponent(T::GetTypeStatic()));
    }

    template<class T>
    T* GetComponent() const {
        return static_cast<T*>(GetComponent(T::GetTypeStatic()));
    }

    template<class T>
    std::vector<T*> GetComponents() const {
        auto            comps = GetComponents(T::GetTypeStatic());
        std::vector<T*> ret;
        for (const auto& comp : comps) {
            ret.push_back(static_cast<T*>(comp));
        }
        return ret;
    }

  private:
    std::vector<Component*> _components;
};

} // namespace EngineS
