#include "Function/Component.hpp"
#include "Function/GameObject.hpp"

namespace EngineS {

void Component::Initialize(GameObject* parent) {
    _gameObject = parent;
    _transform  = _gameObject->transform;
    _renderer   = _gameObject->renderer;
}

} // namespace EngineS