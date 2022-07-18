#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <memory>

#include "Core/Base/Macros.hpp"
#include "Engine.hpp"
#include "Function/Global/Global.hpp"
#include "Function/Input/InputSystem.hpp"
#include "Function/Render/WindowSystem.hpp"

using namespace EngineS;

std::unique_ptr<Engine> engine;

void Update(float deltaTime) {
	if (Global::Instance()->inputSystem->GetKey(KeyCode::Escape)) {
		engine->Shutdown();
	}
}

int main() {
	engine = std::make_unique<Engine>();
	engine->StartEngine();
	engine->Initialize();
	engine->RegisterUpdateFunc(ENGINES_CALLBACK(Update));
	engine->Run();

	return 0;
}