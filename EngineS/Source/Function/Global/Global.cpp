#include "Global.hpp"
#include "Core/Logging/LoggingSystem.hpp"
#include "Function/Input/InputSystem.hpp"
#include "Function/Render/WindowSystem.hpp"

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
	windowSystem = std::make_shared<WindowSystem>();

	loggingSystem = std::make_shared<LoggingSystem>();

	inputSystem = std::make_shared<InputSystem>();
	inputSystem->Initialize();
}

void Global::Shutdown() {
	windowSystem.reset();
	loggingSystem.reset();
	inputSystem.reset();
}

} // namespace EngineS