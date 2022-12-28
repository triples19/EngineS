#include "GameObject.hpp"

namespace EngineS {

GameObject* GameObject::Create() {
    auto obj = new (std::nothrow) GameObject();
    if (obj) {
        obj->AutoRelease();
    }
    return obj;
}

void GameObject::Update(float deltaTime) {
    for (auto& pair : _components) {
        auto& component = pair.second;
        if (component->enabled) {
            component->Update(deltaTime);
        }
    }
}

GameObject::~GameObject() {
    for (const auto& pair : _components) {
        auto& comp = pair.second;
        comp->Release();
    }
}

} // namespace EngineS