#include "InputSystem.hpp"
#include "Core/Base/Macros.hpp"
#include "Function/Global/Global.hpp"
#include "Function/Render/WindowSystem.hpp"

namespace EngineS {

void InputSystem::Initialize() {
#define KEY_CODE(name, code) _keys[KeyCode::name] = {};
#include "Function/Input/KeyCode.def"
#undef KEY_CODE
	Global::Instance()->windowSystem->RegisterOnKeyFunc([this](auto... args) { OnKey(args...); });
}

void InputSystem::Update() {}

bool InputSystem::GetKey(KeyCode key) {
	return _keys[key].downThisFrame;
}

void InputSystem::OnKey(int key, int scanCode, int action, int mods) {
	auto& state			= _keys[static_cast<KeyCode>(key)];
	state.downLastFrame = state.downThisFrame;
	state.downThisFrame = (action != GLFW_RELEASE);
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