#include "GameObject/Transform2D.hpp"

namespace EngineS {

Matrix4x4 Transform2D::MakeModelMatrix() const {
    auto translateMat = Translate(position.x, position.y, 0.0f);
    auto rotateMat    = RotateZ(rotation * Math::Deg2Rad);
    auto scaleMat     = Scale(scale.x, scale.y, 1.0f);
    return translateMat * rotateMat * scaleMat;
}

void Transform2D::Visit(const Matrix4x4& parentModelMat, VisitFunc func) {
    auto model = parentModelMat * MakeModelMatrix();
    func(GetGameObject(), model);
    for (auto& child : _children) {
        child->Visit(model, func);
    }
}

void Transform2D::SetParent(Transform2D* parent) {
    if (_parent)
        _parent->RemoveChild(this);
    _parent = parent;
    _parent->AddChild(this);
}

void Transform2D::AddChild(Transform2D* child) {
    child->_parent = this;
    _children.insert(child);
}

void Transform2D::RemoveChild(Transform2D* child) {
    _children.erase(child);
    child->_parent = nullptr;
}

void Transform2D::RemoveFromParent() {
    if (!_parent)
        return;
    _parent->RemoveChild(this);
}

} // namespace EngineS
