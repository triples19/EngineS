#include "Engine.hpp"
#include "Core/Base/Macros.hpp"
#include "Core/Logging/LoggingSystem.hpp"
#include "Function/Global/Global.hpp"
#include "Function/Input/InputSystem.hpp"
#include "Function/Object/GameObject.hpp"
#include "Function/Render/RenderSystem.hpp"
#include "Function/Render/WindowSystem.hpp"
#include "Function/Scene/SceneManager.hpp"
#include "Resource/ResourceManager.hpp"

namespace EngineS {

void Engine::StartEngine() {
	Global::Instance()->Initialize();
	LOG_INFO("Engine started");
}

void Engine::Shutdown() {
	LOG_INFO("Engine shutting down");
	_shouldShutdown = true;
}

void Engine::Run() {
	auto window = WindowSystem::Instance();
	while (!window->ShouldClose()) {
		const float deltaTime = GetDeltaTime();
		Update(deltaTime);

		if (_shouldShutdown) {
			Global::Instance()->Shutdown();
			break;
		}
	}
}

float Engine::GetDeltaTime() {
	float deltaTime;
	auto  nowTime  = std::chrono::steady_clock::now();
	auto  timeSpan = std::chrono::duration_cast<std::chrono::duration<float>>(nowTime - _lastTickTime);
	deltaTime	   = timeSpan.count();
	_lastTickTime  = nowTime;
	return deltaTime;
}

void Engine::Update(float deltaTime) {
	ResourceManager::Instance()->Update();
	InputSystem::Instance()->Update();
	WindowSystem::Instance()->PollEvents();

	LogicUpdate(deltaTime);
	for (auto& func : _updateFuncs) func(deltaTime);

	RenderUpdate();
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