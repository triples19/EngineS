#include "InputSystem.hpp"
#include "Core/Macros.hpp"
#include "Graphics/WindowSystem.hpp"

namespace EngineS {

static InputSystem* s_SharedInstance;

InputSystem* InputSystem::Instance() {
    if (!s_SharedInstance) {
        s_SharedInstance = new (std::nothrow) InputSystem;
        ES_ASSERT(s_SharedInstance != nullptr);
    }
    return s_SharedInstance;
}

void InputSystem::Initialize() {
#define KEY_CODE(name, code) _keys[KeyCode::name] = {};
#include "KeyCode.def"
#undef KEY_CODE
    WindowSystem::Instance()->RegisterOnKeyFunc(ENGINES_CALLBACK(OnKey));
}

void InputSystem::Update() {
    for (auto& key : _keys) {
        auto& state         = key.second;
        state.downLastFrame = state.downThisFrame;
    }
}

void InputSystem::OnKey(int key, int scanCode, int action, int mods) {
    auto  code          = static_cast<KeyCode>(key);
    auto& state         = _keys[code];
    state.downThisFrame = (action != 0); // GLFW_RELEASE=0
}

bool InputSystem::GetKey(KeyCode key) {
    return _keys[key].downThisFrame;
}

bool InputSystem::GetKeyDown(KeyCode key) {
    auto& state = _keys[key];
    return state.downThisFrame && !state.downLastFrame;
}

bool InputSystem::GetKeyUp(KeyCode key) {
    auto& state = _keys[key];
    return !state.downThisFrame && state.downLastFrame;
}

} // namespace EngineS
