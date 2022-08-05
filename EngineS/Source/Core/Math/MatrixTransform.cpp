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

Matrix4x4 Translate(const Vector3& offset) {
	return Translate(offset.x, offset.y, offset.z);
}

Matrix4x4 Scale(float x, float y, float z) {
	Matrix4x4 m {Matrix4x4::Identity};
	m[0][0] = x;
	m[1][1] = y;
	m[2][2] = z;
	return m;
}

Matrix4x4 Scale(const Vector3& scale) {
	return Scale(scale.x, scale.y, scale.z);
}

Matrix4x4 LookAt(const Vector3& from, const Vector3& to, const Vector3& up) {
	Vector3 x, y, z;
	z = (to - from).Normalized();
	x = Vector3::Cross(up, z).Normalized();
	y = Vector3::Cross(z, x).Normalized();

	Matrix4x4 lookAt;
	lookAt[0][0] = x.x;
	lookAt[1][0] = x.y;
	lookAt[2][0] = x.z;
	lookAt[3][0] = -Vector3::Dot(x, from);
	lookAt[0][1] = y.x;
	lookAt[1][1] = y.y;
	lookAt[2][1] = y.z;
	lookAt[3][1] = -Vector3::Dot(y, from);
	lookAt[0][2] = z.x;
	lookAt[1][2] = z.y;
	lookAt[2][2] = z.z;
	lookAt[3][2] = -Vector3::Dot(z, from);
	lookAt[0][3] = 0;
	lookAt[1][3] = 0;
	lookAt[2][3] = 0;
	lookAt[3][3] = 1.0f;
	return lookAt;
}

} // namespace EngineS