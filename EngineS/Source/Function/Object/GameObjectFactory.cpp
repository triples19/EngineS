#include "GameObjectFactory.hpp"

#include "Function/Global/Global.hpp"
#include "Function/Object/Component/Camera.hpp"
#include "Function/Object/GameObject.hpp"
#include "Function/Render/Shader.hpp"
#include "Function/Render/SpriteRenderer.hpp"
#include "Function/Render/Texture2D.hpp"
#include "Resource/ResourceManager.hpp"

namespace EngineS {
std::shared_ptr<GameObject> GameObjectFactory::CreateSprite(std::filesystem::path path) {
	auto obj			= std::make_shared<GameObject>();
	auto shader			= Global::Instance()->resourceManager->GetDefaultSpriteShader();
	auto texture		= Global::Instance()->resourceManager->LoadTexture2D(path);
	auto spriteRenderer = std::make_unique<SpriteRenderer>(shader, texture);
	obj->AddComponent(std::move(spriteRenderer));
	return obj;
}

std::shared_ptr<GameObject> GameObjectFactory::CreateCamera() {
	auto obj	= std::make_shared<GameObject>();
	auto camera = std::make_unique<Camera>();
	obj->AddComponent(std::move(camera));
	return obj;
}

} // namespace EngineS