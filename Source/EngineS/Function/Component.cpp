#include "Function/Component.hpp"
#include "Function/GameObject.hpp"

namespace EngineS {

void Component::Initialize(GameObject* parent) {
    gameObject = parent;
    transform  = gameObject->transform;
    renderer   = gameObject->renderer;
}

} // namespace EngineS