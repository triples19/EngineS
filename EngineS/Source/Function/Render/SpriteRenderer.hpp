#pragma once

#include <memory>

#include "Core/Base/Types.hpp"
#include "Core/Math/MathHeaders.hpp"
#include "Function/Object/Component/Component.hpp"
#include "Function/Render/Renderer.hpp"

namespace EngineS {

class Program;
class Texture2D;
class Transform2D;
class Material2D;

class SpriteRenderer : public Renderer {
	friend class RenderSystem;

  public:
	SpriteRenderer(std::shared_ptr<Material2D> material);

	virtual void Render(const Matrix4x4& modelMat) override;

	virtual void Initialize(GameObject* parent) override;

  private:
	std::shared_ptr<Material2D> _material;
	Vector3						_color {Vector3::One};
	Vector2						_anchor {0.5f, 0.5f};
};

} // namespace EngineS
