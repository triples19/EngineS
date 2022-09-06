#include "TestScene.hpp"

void TestScene::Initialize() {
	Scene::Initialize();

	auto sprite = GameObjectFactory::CreateSprite("awesomeface.png");
	AddGameObject(sprite);
	auto* transform	 = sprite->GetComponent<Transform2D>();
	transform->scale = {0.2f, 0.2f};
}
