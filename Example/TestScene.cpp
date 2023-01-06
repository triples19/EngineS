#include "TestScene.hpp"
#include "TestComponent.hpp"

#include <vector>

void TestScene::Initialize() {
    Scene::Initialize();

    std::vector<Vector2> positions {{0.0f, 0.0f}, {100.0f, 0.0f}, {-100.0f, 0.0f}, {0.0f, 100.0f}, {0.0f, -100.0f}};

    auto root = GameObjectFactory::CreateGameObject();
    root->AddComponent<TestComponent>();
    AddGameObject(root);

    for (auto& pos : positions) {
        auto sprite = GameObjectFactory::CreateSprite("awesomeface.png");
        AddGameObject(sprite, root->GetComponent<Transform2D>());
        auto* transform     = sprite->GetComponent<Transform2D>();
        transform->scale    = {0.2f, 0.2f};
        transform->position = pos;
        sprite->AddComponent<TestComponent>();
    }
}
