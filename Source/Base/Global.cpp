#include "Global.hpp"

#include "Base/LoggingSystem.hpp"
#include "Base/Macros.hpp"
#include "Function/InputSystem.hpp"
#include "Function/SceneManager.hpp"
#include "Render/RenderSystem.hpp"
#include "Render/WindowSystem.hpp"
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