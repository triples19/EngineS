#pragma once
#include "Math.hpp"

namespace EngineS {

Matrix4x4 Orthographic(float left, float right, float top, float bottom, float near, float far);
Matrix4x4 Orthographic(float width, float height, float near, float far);
Matrix4x4 Translate(float x, float y, float z);
Matrix4x4 Scale(float x, float y, float z);

} // namespace EngineS