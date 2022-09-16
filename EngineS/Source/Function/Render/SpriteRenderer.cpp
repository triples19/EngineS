#include "SpriteRenderer.hpp"

#include "Core/Math/MathHeaders.hpp"
#include "Function/Global/Global.hpp"
#include "Function/Object/Component/Transform2D.hpp"
#include "Function/Render/Program.hpp"
#include "Function/Render/RenderSystem.hpp"
#include "Function/Render/Texture2D.hpp"

namespace EngineS {

SpriteRenderer::SpriteRenderer(std::shared_ptr<Material2D> material) : _material {material} {}

void SpriteRenderer::Render() {
	auto renderSystem = Global::Instance()->renderSystem;
	renderSystem->AddToBatch(_material, transform);
}

void SpriteRenderer::Initialize(GameObject* parent) {
	Renderer::Initialize(parent);
}

} // namespace EngineS