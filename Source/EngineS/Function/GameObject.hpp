#pragma once

#include "Base/Object.hpp"

#include <memory>
#include <type_traits>
#include <typeindex>
#include <unordered_map>
#include <vector>

namespace EngineS {

class Component;
class Renderer;
class Transform2D;

class GameObject : public Object {
  public:
    GameObject() = default;
    ~GameObject();
    virtual void Update(float deltaTime);

    template<class T>
    T* GetComponent() {
        auto iter = _components.find(static_cast<std::type_index>(typeid(T)));
        if (iter == _components.end())
            return nullptr;
        return static_cast<T*>(iter->second);
    }

    template<class T>
    std::vector<T*> GetComponents() {
        auto            range = _components.equal_range(static_cast<std::type_index>(typeid(T)));
        std::vector<T*> comps;
        comps.reserve(std::distance(range.first, range.second));
        for (auto iter = range.first; iter != range.second; ++iter) {
            comps.push_back(static_cast<T*>(iter->second));
        }
        return comps;
    }

    template<class T>
    T* AddComponent() {
        auto comp = new T;
        comp->Retain();
        comp->Initialize(this);
        auto inserted = _components.insert(std::make_pair(static_cast<std::type_index>(typeid(T)), comp));
        auto pointer  = static_cast<T*>(inserted->second);
        SetPropertyIfNeeded(pointer);
        return static_cast<T*>(pointer);
    }

  private:
    template<class T>
    void SetPropertyIfNeeded(T* val) {
        if constexpr (std::is_base_of_v<Renderer, T>) {
            renderer = val;
        } else if constexpr (std::is_base_of_v<Transform2D, T>) {
            transform = val;
        }
    }

  public:
    Transform2D* transform {nullptr};
    Renderer*    renderer {nullptr};

  private:
    std::unordered_multimap<std::type_index, Component*> _components;
};

} // namespace EngineS
