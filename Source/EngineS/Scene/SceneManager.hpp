#pragma once

#include "Base/Object.hpp"

#include <memory>

namespace EngineS {

class Scene;

class SceneManager : public Object {
    ES_OBJECT
  public:
    static SceneManager* Instance();

    void Initialize();

    void   SetCurrentScene(Scene* scene);
    Scene* GetCurrentScene() { return _currentScene; }

  private:
    Scene* _currentScene {nullptr};
};

} // namespace EngineS
