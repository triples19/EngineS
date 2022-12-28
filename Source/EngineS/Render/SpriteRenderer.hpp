#pragma once

#include <memory>

#include "Function/Component.hpp"
#include "Math/Math.hpp"
#include "Render/BufferTypes.hpp"
#include "Renderer.hpp"

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

    const Vector2& GetAnchor() const { return _anchor; }
    void           SetAnchor(const Vector2& anchor) { _anchor = anchor; }
    const Color4F& GetColor() const { return _color; }
    void           SetColor(const Color4F& color) { _color = color; }

  private:
    std::shared_ptr<Material2D> _material;
    Color4F                     _color {Color4F::White};
    Vector2                     _anchor {0.5f, 0.5f};
};

} // namespace EngineS
