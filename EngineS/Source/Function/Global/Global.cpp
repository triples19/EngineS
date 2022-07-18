#include "Global.hpp"
#include "Core/Logging/LoggingSystem.hpp"
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
	windowSystem = new WindowSystem;

	loggingSystem = new LoggingSystem;
}

void Global::Shutdown() {
	delete windowSystem;
}

} // namespace EngineS