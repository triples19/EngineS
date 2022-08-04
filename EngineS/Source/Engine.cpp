#include "Engine.hpp"
#include "Core/Base/Macros.hpp"
#include "Core/Logging/LoggingSystem.hpp"
#include "Function/Global/Global.hpp"
#include "Function/Input/InputSystem.hpp"
#include "Function/Render/RenderSystem.hpp"
#include "Function/Render/WindowSystem.hpp"

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
	auto window = Global::Instance()->windowSystem;
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
	Global::Instance()->inputSystem->Update();
	Global::Instance()->windowSystem->PollEvents();

	LogicUpdate(deltaTime);
	for (auto& func : _updateFuncs) func(deltaTime);

	RenderUpdate();
}

void Engine::LogicUpdate(float deltaTime) {}

void Engine::RenderUpdate() {
	Global::Instance()->renderSystem->Update();
}

} // namespace EngineS