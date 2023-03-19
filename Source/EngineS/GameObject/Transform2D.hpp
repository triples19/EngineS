#pragma once

#include "GameObject/Component.hpp"
#include "Math/Math.hpp"

#include <functional>
#include <unordered_set>

namespace EngineS {

class GameObject;

class Transform2D : public Component {
    ES_OBJECT
  public:
    Vector2 position {0.0f, 0.0f};
    Vector2 scale {1.0f, 1.0f};
    float   rotation {0.0f};

    Matrix4x4 MakeModelMatrix() const;

    using VisitFunc = std::function<void(GameObject*, const Matrix4x4&)>;
    void Visit(const Matrix4x4& parentModelMat, VisitFunc func);

    Transform2D* GetParent() { return _parent; }
    void         SetParent(Transform2D* parent);
    void         AddChild(Transform2D* child);
    void         RemoveChild(Transform2D* child);
    void         RemoveFromParent();
    auto&        GetChildren() { return _children; }

  private:
    std::unordered_set<Transform2D*> _children;
    Transform2D*                     _parent {nullptr};
};

} // namespace EngineS
