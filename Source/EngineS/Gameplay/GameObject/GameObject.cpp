#include "GameObject.hpp"
#include "Component.hpp"
#include "Core/IO/Logger.hpp"
#include "Core/Reflection/Constructor.hpp"
#include "Core/Reflection/Type.hpp"

namespace EngineS {

GameObject::~GameObject() {
    for (const auto& comp : _components) {
        comp->Release();
    }
}

void GameObject::Update(float deltaTime) {
    for (const auto& comp : _components) {
        if (comp->GetEnabled()) {
            comp->Update(deltaTime);
        }
    }
}

Component* GameObject::AddComponent(const Type* type) {
    auto comp = type->GetConstructor({})->Invoke().GetValue<Component*>();
    if (!comp) {
        Logger::Error("Failed to create component of {}", type->GetName());
        return nullptr;
    }
    comp->Retain();
    comp->Initialize(this);
    _components.push_back(comp);
    return comp;
}

Component* GameObject::GetComponent(const Type* type) const {
    for (const auto& comp : _components) {
        if (comp->GetType()->DerivedFrom(type)) {
            return comp;
        }
    }
    return nullptr;
}

std::vector<Component*> GameObject::GetComponents(const Type* type) const {
    std::vector<Component*> comps;
    for (auto& comp : _components) {
        if (comp->GetType()->DerivedFrom(type)) {
            comps.push_back(comp);
        }
    }
    return comps;
}

} // namespace EngineS
