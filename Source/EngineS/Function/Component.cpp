#include "Function/Component.hpp"
#include "Function/GameObject.hpp"
#include "Reflection/Type.hpp"

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