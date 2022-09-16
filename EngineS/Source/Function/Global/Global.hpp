#pragma once

#include <memory>

namespace EngineS {

class WindowSystem;
class LoggingSystem;
class InputSystem;
class RenderSystem;
class ResourceManager;
class SceneManager;

class Global {
  public:
	static Global* Instance();

	void Initialize();
	void Shutdown();

  public:
	//	std::shared_ptr<WindowSystem>	 windowSystem;
	//	std::shared_ptr<RenderSystem>	 renderSystem;
	//	std::shared_ptr<LoggingSystem>	 loggingSystem;
	//	std::shared_ptr<InputSystem>	 inputSystem;
	//	std::shared_ptr<ResourceManager> resourceManager;
	//	std::shared_ptr<SceneManager>	 sceneManager;
};

} // namespace EngineS