#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <filesystem>
#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>

#include "Core/Base/Macros.hpp"
#include "Engine.hpp"
#include "Function/Global/Global.hpp"
#include "Function/Input/InputSystem.hpp"
#include "Function/Object/Component/Transform2D.hpp"
#include "Function/Object/GameObject.hpp"
#include "Function/Render/WindowSystem.hpp"
#include "Resource/ResourceManager.hpp"

using namespace EngineS;

std::unique_ptr<Engine> engine;

int main() {
	engine = std::make_unique<Engine>();
	engine->StartEngine();
	engine->Run();

	return 0;
}