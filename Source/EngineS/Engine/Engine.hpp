#pragma once

#include <chrono>
#include <functional>
#include <vector>

namespace EngineS {

class Engine {
  public:
    static Engine* Instance();

    void StartEngine();
    void Shutdown();
    void Run();

    int GetFPS() const { return _fpsCalculator.fps; }

    using UpdateFunc = std::function<void(float)>;
    void RegisterUpdateFunc(UpdateFunc func) { _updateFuncs.push_back(func); }

  private:
    float GetDeltaTime();
    void  Update(float deltaTime);
    void  LogicUpdate(float deltaTime);
    void  RenderUpdate();

  private:
    struct FPSCalculator {
        static constexpr float fpsSmoothing = 0.1f;
        int                    frameCount;
        float                  averageDuration;
        int                    fps;

        int Calculate(float deltaTime);
    };

    FPSCalculator _fpsCalculator;

    std::chrono::steady_clock::time_point _lastTickTime {std::chrono::steady_clock::now()};
    std::vector<UpdateFunc>               _updateFuncs;

    bool _shouldShutdown {false};
};

} // namespace EngineS