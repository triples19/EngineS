#include "Engine/Engine.hpp"
#include "Base/AutoReleasePool.hpp"
#include "Base/Macros.hpp"
#include "Function/GameObject.hpp"
#include "Function/InputSystem.hpp"
#include "Function/Scene.hpp"
#include "Function/SceneManager.hpp"
#include "IO/Logger.hpp"
#include "Render/RenderSystem.hpp"
#include "Render/WindowSystem.hpp"
#include "Resource/ResourceManager.hpp"

namespace EngineS {

static Engine* s_SharedInstance;

Engine* Engine::Instance() {
    if (!s_SharedInstance) {
        s_SharedInstance = new (std::nothrow) Engine;
        assert(s_SharedInstance != nullptr);
        s_SharedInstance->Retain();
    }
    return s_SharedInstance;
}

int Engine::FPSCalculator::Calculate(float deltaTime) {
    frameCount++;
    if (frameCount == 1) {
        averageDuration = deltaTime;
    } else {
        averageDuration = averageDuration * (1 - fpsSmoothing) + deltaTime * fpsSmoothing;
    }
    fps = static_cast<int>(1.0f / averageDuration);
    return fps;
}

void Engine::StartEngine() {
    WindowSystem::Instance()->Retain();
    RenderSystem::Instance()->Retain();
    InputSystem::Instance()->Retain();
    SceneManager::Instance()->Retain();
    ResourceManager::Instance()->Retain();

    WindowSystem::Instance()->Initialize();
    RenderSystem::Instance()->Initialize();
    InputSystem::Instance()->Initialize();
    SceneManager::Instance()->Initialize();

    ResourceManager::Instance()->AddResourceDir("../Assets");

    Logger::Info("Engine started");
}

void Engine::Shutdown() {
    Logger::Info("Engine shutting down");
    _shouldShutdown = true;
}

void Engine::Run() {
    auto window = WindowSystem::Instance();
    while (!window->ShouldClose()) {
        const float deltaTime = GetDeltaTime();
        Update(deltaTime);

        if (_shouldShutdown) {
            break;
        }
    }
}

float Engine::GetDeltaTime() {
    float deltaTime;
    auto  nowTime  = std::chrono::steady_clock::now();
    auto  timeSpan = std::chrono::duration_cast<std::chrono::duration<float>>(nowTime - _lastTickTime);
    deltaTime      = timeSpan.count();
    _lastTickTime  = nowTime;
    return deltaTime;
}

void Engine::Update(float deltaTime) {
    ResourceManager::Instance()->Update();
    InputSystem::Instance()->Update();
    WindowSystem::Instance()->PollEvents();

    LogicUpdate(deltaTime);
    for (auto& func : _updateFuncs) func(deltaTime);

    _fpsCalculator.Calculate(deltaTime);

    RenderUpdate();

    PoolManager::Instance()->GetCurrentPool()->Clear();
}

void Engine::LogicUpdate(float deltaTime) {
    const auto& objs = SceneManager::Instance()->GetCurrentScene()->GetGameObjects();
    for (auto& obj : objs) {
        obj->Update(deltaTime);
    }
}

void Engine::RenderUpdate() {
    RenderSystem::Instance()->Update();
}

} // namespace EngineS