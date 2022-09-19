#include <EngineS.hpp>

#include <filesystem>
#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>

#include "TestScene.hpp"

using namespace EngineS;

std::unique_ptr<Engine> engine;

int main() {
	engine = std::make_unique<Engine>();
	engine->StartEngine();
	auto scene = std::make_unique<TestScene>();
	scene->Initialize();
	SceneManager::Instance()->SetCurrentScene(std::move(scene));
	engine->Run();

	return 0;
}