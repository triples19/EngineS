#include "TestScene.hpp"

#include "Function/Object/GameObject.hpp"
#include "Function/Object/GameObjectFactory.hpp"

namespace EngineS {

void TestScene::Initialize() {
	Scene::Initialize();

	auto sprite = GameObjectFactory::CreateSprite("awesomeface.png");
	AddGameObject(sprite);
}

} // namespace EngineS