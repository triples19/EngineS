#include "Scene.hpp"

#include "Function/Global/Global.hpp"
#include "Function/Object/Component/Camera.hpp"
#include "Function/Render/SpriteRenderer.hpp"
#include "Function/Render/WindowSystem.hpp"

#include "Function/Object/GameObject.hpp"
#include "Function/Object/GameObjectFactory.hpp"

namespace EngineS {

void Scene::Initialize() {
	auto windowSystem	 = WindowSystem::Instance();
	auto [width, height] = windowSystem->GetWindowSize();

	auto  cameraObj = GameObjectFactory::CreateCamera();
	auto* camera	= cameraObj->GetComponent<Camera>();

	camera->width  = width;
	camera->height = height;
	camera->near   = -1.0f;
	camera->far	   = 1.0f;
	camera->ConstructProjectionMatrix();
	AddGameObject(cameraObj);
	_mainCamera = camera;
}

} // namespace EngineS