#pragma once

#include <memory>

#include "Core/Math/Math.hpp"
#include "Core/Memory/SharedPtr.hpp"
#include "Gameplay/GameObject/Component.hpp"
#include "Graphics/API/BufferTypes.hpp"
#include "Graphics/API/Renderer.hpp"
#include "Graphics/Material2D.hpp"

namespace EngineS {

class Buffer;
class RenderPipeline;
class DrawList;

class SpriteRenderer : public Renderer {
    ES_OBJECT
    friend class RenderSystem;

  public:
    SpriteRenderer();
    ~SpriteRenderer();

    virtual void Render(const Matrix4x4& modelMat, DrawList* drawList) override;

    virtual void Initialize(GameObject* parent) override;

    void        SetMaterial(Material2D* material) { _material = material; }
    Material2D* GetMaterial() { return _material.Get(); }

    const Vector2& GetAnchor() const { return _anchor; }
    void           SetAnchor(const Vector2& anchor) { _anchor = anchor; }
    const Color4F& GetColor() const { return _color; }
    void           SetColor(const Color4F& color) { _color = color; }

  private:
    SharedPtr<Material2D> _material;
    Color4F               _color {Color4F::White};
    Vector2               _anchor {0.5f, 0.5f};
    Buffer*               _vertexBuffer;
};

} // namespace EngineS
