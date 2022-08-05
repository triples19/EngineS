#pragma once
#include "Math.hpp"

namespace EngineS {

Matrix4x4 Orthographic(float left, float right, float top, float bottom, float near, float far);
Matrix4x4 Orthographic(float width, float height, float near, float far);
Matrix4x4 Translate(float x, float y, float z);
Matrix4x4 Translate(const Vector3& offset);
Matrix4x4 Scale(float x, float y, float z);
Matrix4x4 Scale(const Vector3& scale);
Matrix4x4 LookAt(const Vector3& from, const Vector3& to, const Vector3& up);

} // namespace EngineS