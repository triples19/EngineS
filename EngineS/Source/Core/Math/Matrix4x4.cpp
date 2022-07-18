#include "Matrix4x4.hpp"
#include "Vector2.hpp"
#include "Vector3.hpp"
#include "Vector4.hpp"

namespace EngineS {

const Matrix4x4 Matrix4x4::Identity {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1};

const Matrix4x4 Matrix4x4::Zero {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

Matrix4x4::Matrix4x4(const Vector4& row0, const Vector4& row1, const Vector4& row2, const Vector4& row3) {
	mat[0][0] = row0.x;
	mat[0][1] = row0.y;
	mat[0][2] = row0.z;
	mat[0][3] = row0.w;
	mat[1][0] = row1.x;
	mat[1][1] = row1.y;
	mat[1][2] = row1.z;
	mat[1][3] = row1.w;
	mat[2][0] = row2.x;
	mat[2][1] = row2.y;
	mat[2][2] = row2.z;
	mat[2][3] = row2.w;
	mat[3][0] = row3.x;
	mat[3][1] = row3.y;
	mat[3][2] = row3.z;
	mat[3][3] = row3.w;
}

Vector4 Matrix4x4::operator*(const Vector4& v) const {
	return Vector4(mat[0][0] * v.x + mat[0][1] * v.y + mat[0][2] * v.z + mat[0][3] * v.w,
				   mat[1][0] * v.x + mat[1][1] * v.y + mat[1][2] * v.z + mat[1][3] * v.w,
				   mat[2][0] * v.x + mat[2][1] * v.y + mat[2][2] * v.z + mat[2][3] * v.w,
				   mat[3][0] * v.x + mat[3][1] * v.y + mat[3][2] * v.z + mat[3][3] * v.w);
}

} // namespace EngineS