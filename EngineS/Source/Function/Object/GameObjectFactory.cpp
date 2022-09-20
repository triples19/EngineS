#include "GameObjectFactory.hpp"

#include "Function/Global/Global.hpp"
#include "Function/Object/Component/Camera.hpp"
#include "Function/Object/Component/Transform2D.hpp"
#include "Function/Object/GameObject.hpp"
#include "Function/Render/Program.hpp"
#include "Function/Render/RenderSystem.hpp"
#include "Function/Render/SpriteRenderer.hpp"
#include "Function/Render/Texture2D.hpp"
#include "Resource/ResourceManager.hpp"

namespace EngineS {

std::shared_ptr<GameObject> GameObjectFactory::CreateGameObject() {
	auto obj = std::make_shared<GameObject>();
	obj->AddComponent<Transform2D>();
	return obj;
}

std::shared_ptr<GameObject> GameObjectFactory::CreateSprite(std::filesystem::path path) {
	auto obj		   = CreateGameObject();
	auto textureHandle = ResourceManager::Instance()->GetHandle<Texture2D>(path);
	textureHandle.Load();
	auto programHandle = ResourceManager::Instance()->GetHandle<Program>("sprite.glsl");
	programHandle.Load();
	auto material = RenderSystem::Instance()->GetOrCreateMaterial(*programHandle, *textureHandle);
	obj->AddComponent<SpriteRenderer>(material);
	return obj;
}

std::shared_ptr<GameObject> GameObjectFactory::CreateCamera() {
	auto obj = CreateGameObject();
	obj->AddComponent<Camera>();
	return obj;
}

} // namespace EngineS