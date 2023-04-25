#include "Scene.hpp"
#include "Gameplay/GameObject/GameObject.hpp"
#include "Gameplay/GameObject/GameObjectFactory.hpp"
#include "Gameplay/GameObject/Transform2D.hpp"
#include "Graphics/Camera.hpp"
#include "Graphics/SpriteRenderer.hpp"
#include "Graphics/WindowSystem.hpp"

namespace EngineS {

Scene::Scene() = default;

Scene::~Scene() {
    _rootGameObject->Release();
}

void Scene::Initialize() {
    _rootGameObject = GameObjectFactory::CreateGameObject();
    _rootGameObject->Retain();
    _gameObjects.insert(_rootGameObject);

    auto windowSystem    = WindowSystem::Instance();
    auto [width, height] = windowSystem->GetWindowSize();

    auto  cameraObj = GameObjectFactory::CreateCamera();
    auto* camera    = cameraObj->GetComponent<Camera>();

    camera->width  = width;
    camera->height = height;
    camera->near   = -1.0f;
    camera->far    = 1.0f;
    camera->ConstructProjectionMatrix();
    AddGameObject(cameraObj);
    _mainCamera = camera;
}

void Scene::AddGameObject(GameObject* gameObject) {
    AddGameObject(gameObject, _rootGameObject->GetComponent<Transform2D>());
}

void Scene::AddGameObject(GameObject* gameObject, Transform2D* parent) {
    _gameObjects.insert(gameObject);
    parent->AddChild(gameObject->GetComponent<Transform2D>());
    gameObject->Retain();
}

void Scene::RemoveGameObject(GameObject* gameObject) {
    _gameObjects.erase(gameObject);
    gameObject->Release();
}

Transform2D* Scene::GetRootTransform() {
    return _rootGameObject->GetComponent<Transform2D>();
}

} // namespace EngineS
