#include "GameObjectFactory.hpp"
#include "GameObject.hpp"
#include "Graphics/API/Program.hpp"
#include "Graphics/API/RenderDevice.hpp"
#include "Graphics/API/Texture2D.hpp"
#include "Graphics/Camera.hpp"
#include "Graphics/Material2D.hpp"
#include "Graphics/RenderSystem.hpp"
#include "Graphics/SpriteRenderer.hpp"
#include "Resource/ResourceManager.hpp"
#include "Transform2D.hpp"

namespace EngineS {

GameObject* GameObjectFactory::CreateGameObject() {
    auto obj = new GameObject();
    obj->AddComponent<Transform2D>();
    return obj;
}

GameObject* GameObjectFactory::CreateSprite(std::filesystem::path path) {
    auto obj      = CreateGameObject();
    auto texture  = ResourceManager::Instance()->Load(RenderDevice::Instance()->GetTexture2DType(), path);
    auto program  = ResourceManager::Instance()->Load(RenderDevice::Instance()->GetProgramType(), "sprite.glsl");
    auto material = new Material2D(dynamic_cast<Program*>(program), dynamic_cast<Texture2D*>(texture));
    auto renderer = obj->AddComponent<SpriteRenderer>();
    renderer->SetMaterial(material);
    return obj;
}

GameObject* GameObjectFactory::CreateCamera() {
    auto obj = CreateGameObject();
    obj->AddComponent<Camera>();
    return obj;
}

} // namespace EngineS
