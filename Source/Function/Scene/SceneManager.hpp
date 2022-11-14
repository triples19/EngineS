#pragma once

#include "Scene.hpp"

#include <memory>

namespace EngineS {

class SceneManager {
  public:
	static SceneManager* Instance();

	void Initialize();

	void   SetCurrentScene(std::unique_ptr<Scene> scene) { _currentScene = std::move(scene); }
	Scene* GetCurrentScene() { return _currentScene.get(); }

  private:
	std::unique_ptr<Scene> _currentScene;
};

} // namespace EngineS
