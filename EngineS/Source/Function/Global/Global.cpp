#include "Global.hpp"
#include "Core/Logging/LoggingSystem.hpp"
#include "Function/Input/InputSystem.hpp"
#include "Function/Render/RenderSystem.hpp"
#include "Function/Render/WindowSystem.hpp"
#include "Resource/ResourceManager.hpp"

#include <cassert>
#include <new>

namespace EngineS {

static Global* globalInstance;

Global* Global::Instance() {
	if (!globalInstance) {
		globalInstance = new (std::nothrow) Global;
		assert(globalInstance != nullptr);
	}
	return globalInstance;
}

void Global::Initialize() {
	loggingSystem = std::make_shared<LoggingSystem>();

	resourceManager = std::make_shared<ResourceManager>();
	resourceManager->Initialize();

	windowSystem = std::make_shared<WindowSystem>();
	renderSystem = std::make_shared<RenderSystem>();
	renderSystem->PreWindowInitialize();
	windowSystem->Initialize(1280, 720, "EngineS");
	renderSystem->Initialize();

	inputSystem = std::make_shared<InputSystem>();
	inputSystem->Initialize();

	resourceManager->LoadDefaultResources();
}

void Global::Shutdown() {
	windowSystem.reset();
	loggingSystem.reset();
	inputSystem.reset();
	resourceManager.reset();
	renderSystem.reset();
}

} // namespace EngineS