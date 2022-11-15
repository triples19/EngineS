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
};

} // namespace EngineS