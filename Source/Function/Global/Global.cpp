#include "Global.hpp"

#include "Core/Base/Macros.hpp"
#include "Core/Logging/LoggingSystem.hpp"
#include "Function/Input/InputSystem.hpp"
#include "Function/Render/RenderSystem.hpp"
#include "Function/Render/WindowSystem.hpp"
#include "Function/Scene/SceneManager.hpp"
#include "Resource/ResourceManager.hpp"

#include <new>

namespace EngineS {

static Global* globalInstance;

Global* Global::Instance() {
	if (!globalInstance) {
		globalInstance = new (std::nothrow) Global;
		ES_ASSERT_NOMSG(globalInstance != nullptr);
	}
	return globalInstance;
}

void Global::Initialize() {
	ResourceManager::Instance()->Initialize();

	WindowSystem::Instance();
	RenderSystem::Instance();
	RenderSystem::Instance()->PreWindowInitialize();
	WindowSystem::Instance()->Initialize(512, 512, "EngineS");
	RenderSystem::Instance()->Initialize();

	InputSystem::Instance()->Initialize();
	SceneManager::Instance()->Initialize();
}

void Global::Shutdown() {}

} // namespace EngineS