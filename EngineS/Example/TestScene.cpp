#include "TestScene.hpp"

#include "TestComponent.hpp"

#include <vector>

void TestScene::Initialize() {
	Scene::Initialize();

	std::vector<Vector2> positions {{0.0f, 0.0f}, {100.0f, 0.0f}, {-100.0f, 0.0f}, {0.0f, 100.0f}, {0.0f, -100.0f}};

	for (auto& pos : positions) {
		auto sprite = GameObjectFactory::CreateSprite("awesomeface.png");
		AddGameObject(sprite);
		auto* transform = sprite->GetComponent<Transform2D>();
		transform->SetLocalScale({0.2f, 0.2f});
		transform->SetLocalPosition(pos);
		sprite->AddComponent<TestComponent>();
	}
}
