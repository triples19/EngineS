#include "Scene.hpp"

#include "Function/Global/Global.hpp"
#include "Function/Object/Component/Camera.hpp"
#include "Function/Object/Component/Transform2D.hpp"
#include "Function/Object/GameObject.hpp"
#include "Function/Object/GameObjectFactory.hpp"
#include "Function/Render/SpriteRenderer.hpp"
#include "Function/Render/WindowSystem.hpp"

namespace EngineS {

Scene::Scene() = default;

Scene::~Scene() {
	_rootGameObject->Release();
}

void Scene::Initialize() {
	_rootGameObject = GameObjectFactory::CreateGameObject();
	_rootGameObject->Retain();
	_gameObjects.insert(_rootGameObject);

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

void Scene::AddGameObject(GameObject* gameObject) {
	AddGameObject(gameObject, _rootGameObject->transform);
}

void Scene::AddGameObject(GameObject* gameObject, Transform2D* parent) {
	_gameObjects.insert(gameObject);
	parent->AddChild(gameObject->transform);
	gameObject->Retain();
}

void Scene::RemoveGameObject(GameObject* gameObject) {
	_gameObjects.erase(gameObject);
	gameObject->Release();
}

Transform2D* Scene::GetRootTransform() {
	return _rootGameObject->transform;
}

} // namespace EngineS