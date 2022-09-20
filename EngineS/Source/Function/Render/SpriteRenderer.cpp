#include "SpriteRenderer.hpp"

#include "Core/Math/MathHeaders.hpp"
#include "Function/Global/Global.hpp"
#include "Function/Object/Component/Transform2D.hpp"
#include "Function/Object/GameObject.hpp"
#include "Function/Render/Program.hpp"
#include "Function/Render/RenderSystem.hpp"
#include "Function/Render/Texture2D.hpp"

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