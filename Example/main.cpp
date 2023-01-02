#include <EngineS.hpp>

#include "TestScene.hpp"

using namespace EngineS;

void TestUpdate(float deltaTime) {
    WindowSystem::Instance()->SetTitle(fmt::format("EngineS | FPS: {}", Engine::Instance()->GetFPS()));
}

int main() {
    auto* engine = Engine::Instance();
    engine->StartEngine();
    engine->RegisterUpdateFunc(ENGINES_CALLBACK(TestUpdate));
    auto scene = new TestScene;
    scene->Initialize();
    SceneManager::Instance()->SetCurrentScene(scene);
    engine->Run();

    return 0;
}