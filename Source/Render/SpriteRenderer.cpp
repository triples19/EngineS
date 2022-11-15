#include "SpriteRenderer.hpp"

#include "Base/Global.hpp"
#include "Function/GameObject.hpp"
#include "Function/Transform2D.hpp"
#include "Math/MathHeaders.hpp"
#include "Program.hpp"
#include "RenderSystem.hpp"
#include "Texture2D.hpp"

namespace EngineS {

SpriteRenderer::SpriteRenderer(std::shared_ptr<Material2D> material) : _material {material} {}

void SpriteRenderer::Render(const Matrix4x4& modelMat) {
    auto renderSystem = RenderSystem::Instance();
    renderSystem->AddToBatch(_material, modelMat, _anchor, _color);
}

void SpriteRenderer::Initialize(GameObject* parent) {
    Renderer::Initialize(parent);
}

} // namespace EngineS