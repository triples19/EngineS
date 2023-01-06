#include "Camera.hpp"

#include "Transform2D.hpp"

namespace EngineS {

void Camera::Initialize(GameObject* parent) {
    Component::Initialize(parent);
}

void Camera::Update(float deltaTime) {
    Component::Update(deltaTime);
}

void Camera::ConstructProjectionMatrix() {
    _projMat = Orthographic(width, height, near, far);
}

const Matrix4x4& Camera::GetProjectionMatrix() const {
    return _projMat;
}

Matrix4x4 Camera::GetViewMatrix() const {
    //	return LookAt(static_cast<Vector3>(transform->position),
    //				  static_cast<Vector3>(transform->position) + Vector3(0, 0, 1),
    //				  Vector3(0, 1, 0));
    return GetComponent<Transform2D>()->MakeModelMatrix().InverseAffine();
}

} // namespace EngineS