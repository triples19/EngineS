#include "GameObjectFactory.hpp"

#include "Base/Global.hpp"
#include "Function/Camera.hpp"
#include "Function/Transform2D.hpp"
#include "GameObject.hpp"
#include "Render/Program.hpp"
#include "Render/RenderSystem.hpp"
#include "Render/SpriteRenderer.hpp"
#include "Render/Texture2D.hpp"
#include "Resource/ResourceManager.hpp"

namespace EngineS {

GameObject* GameObjectFactory::CreateGameObject() {
	auto obj = GameObject::Create();
	obj->AddComponent<Transform2D>();
	return obj;
}

GameObject* GameObjectFactory::CreateSprite(std::filesystem::path path) {
	auto obj		   = CreateGameObject();
	auto textureHandle = ResourceManager::Instance()->GetHandle<Texture2D>(path);
	textureHandle.Load();
	auto programHandle = ResourceManager::Instance()->GetHandle<Program>("sprite.glsl");
	programHandle.Load();
	auto material = RenderSystem::Instance()->GetOrCreateMaterial(*programHandle, *textureHandle);
	obj->AddComponent<SpriteRenderer>(material);
	return obj;
}

GameObject* GameObjectFactory::CreateCamera() {
	auto obj = CreateGameObject();
	obj->AddComponent<Camera>();
	return obj;
}

} // namespace EngineS