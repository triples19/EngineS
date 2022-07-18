#pragma once

namespace EngineS {

class WindowSystem;
class LoggingSystem;
class InputSystem;

class Global {
  public:
	static Global* Instance();

	void Initialize();
	void Shutdown();

  public:
	WindowSystem*  windowSystem;
	LoggingSystem* loggingSystem;
	InputSystem*   inputSystem;
};

} // namespace EngineS