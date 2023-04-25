#include "Component.hpp"
#include "Core/Reflection/Type.hpp"
#include "GameObject.hpp"

namespace EngineS {

void Component::Initialize(GameObject* parent) {
    _gameObject = parent;
}

Component* Component::GetComponent(const Type* type) const {
    return _gameObject->GetComponent(type);
}

std::vector<Component*> Component::GetComponents(const Type* type) const {
    return _gameObject->GetComponents(type);
}

} // namespace EngineS
