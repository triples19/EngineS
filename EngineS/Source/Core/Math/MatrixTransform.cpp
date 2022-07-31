#include "MatrixTransform.hpp"
#include "Matrix4x4.hpp"
#include "Vector3.hpp"

namespace EngineS {

Matrix4x4 Orthographic(float left, float right, float top, float bottom, float near, float far) {
	Matrix4x4 m {Matrix4x4::Zero};
	m[0][0] = 2 / (right - left);
	m[0][3] = -(right + left) / (right - left);
	m[1][1] = 2 / (top - bottom);
	m[1][3] = -(top + bottom) / (top - bottom);
	m[2][2] = -2 / (far - near);
	m[2][3] = -(far + near) / (far - near);
	m[3][3] = 1;
	return m;
}

Matrix4x4 Orthographic(float width, float height, float near, float far) {
	Matrix4x4 m {Matrix4x4::Zero};
	m[0][0] = 2 / width;
	m[1][1] = 2 / height;
	m[2][2] = -2 / (far - near);
	m[2][3] = -(far + near) / (far - near);
	m[3][3] = 1;
	return m;
}

Matrix4x4 Translate(float x, float y, float z) {
	Matrix4x4 m {Matrix4x4::Identity};
	m[0][3] = x;
	m[1][3] = y;
	m[2][3] = z;
	return m;
}

Matrix4x4 Translate(Vector3 offset) {
	return Translate(offset.x, offset.y, offset.z);
}

Matrix4x4 Scale(float x, float y, float z) {
	Matrix4x4 m {Matrix4x4::Identity};
	m[0][0] = x;
	m[1][1] = y;
	m[2][2] = z;
	return m;
}

Matrix4x4 Scale(Vector3 scale) {
	return Scale(scale.x, scale.y, scale.z);
}

} // namespace EngineS