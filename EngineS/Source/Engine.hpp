#pragma once

#include <chrono>
#include <functional>
#include <vector>

namespace EngineS {

class Engine {
  public:
	void StartEngine();
	void Shutdown();
	void Run();

	using UpdateFunc = std::function<void(float)>;
	void RegisterUpdateFunc(UpdateFunc func) { _updateFuncs.push_back(func); }

  private:
	float GetDeltaTime();
	void  Update(float deltaTime);
	void  LogicUpdate(float deltaTime);
	void  RenderUpdate();

  private:
	std::chrono::steady_clock::time_point _lastTickTime {std::chrono::steady_clock::now()};
	std::vector<UpdateFunc>				  _updateFuncs;

	bool _shouldShutdown {false};
};

} // namespace EngineS