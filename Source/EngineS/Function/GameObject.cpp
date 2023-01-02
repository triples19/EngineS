#include "Function/GameObject.hpp"
#include "Function/Component.hpp"

namespace EngineS {

void GameObject::Update(float deltaTime) {
    for (auto& pair : _components) {
        auto& component = pair.second;
        if (component->GetEnabled()) {
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