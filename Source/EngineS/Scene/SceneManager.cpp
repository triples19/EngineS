#include "Scene/SceneManager.hpp"
#include "Base/Macros.hpp"
#include "Scene/Scene.hpp"

namespace EngineS {

static SceneManager* s_SharedInstance;

SceneManager* SceneManager::Instance() {
    if (!s_SharedInstance) {
        s_SharedInstance = new (std::nothrow) SceneManager;
        ES_ASSERT_NOMSG(s_SharedInstance != nullptr);
    }
    return s_SharedInstance;
}

void SceneManager::Initialize() {}

void EngineS::SceneManager::SetCurrentScene(EngineS::Scene* scene) {
    if (_currentScene)
        _currentScene->Release();
    _currentScene = scene;
    _currentScene->Retain();
}

} // namespace EngineS
