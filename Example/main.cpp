#include <EngineS.hpp>

#include <filesystem>
#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>

#include "TestScene.hpp"

using namespace EngineS;

void TestUpdate(float deltaTime) {
	WindowSystem::Instance()->SetTitle(fmt::format("EngineS | FPS: {}", GameEngine::Instance()->GetFPS()));
}

int main() {
	auto* engine = GameEngine::Instance();
	engine->StartEngine();
	engine->RegisterUpdateFunc(ENGINES_CALLBACK(TestUpdate));
	auto scene = std::make_unique<TestScene>();
	scene->Initialize();
	SceneManager::Instance()->SetCurrentScene(std::move(scene));
	engine->Run();

	return 0;
}