#include "Matrix3x3.hpp"
#include "Vector3.hpp"

namespace EngineS {

const Matrix3x3 Matrix3x3::Identity {1, 0, 0, 0, 1, 0, 0, 0, 1};
const Matrix3x3 Matrix3x3::Zero {0, 0, 0, 0, 0, 0, 0, 0, 0};

Matrix3x3::Matrix3x3(const Vector3& row0, const Vector3& row1, const Vector3& row2) {
	mat[0][0] = row0.x;
	mat[0][1] = row0.y;
	mat[0][2] = row0.z;
	mat[1][0] = row1.x;
	mat[1][1] = row1.y;
	mat[1][2] = row1.z;
	mat[2][0] = row2.x;
	mat[2][1] = row2.y;
	mat[2][2] = row2.z;
}

Vector3 Matrix3x3::GetColumn(size_t iCol) const {
	assert(0 <= iCol && iCol < 3);
	return Vector3(mat[0][iCol], mat[1][iCol], mat[2][iCol]);
}

void Matrix3x3::SetColumn(size_t iCol, const Vector3& vec) {
	mat[0][iCol] = vec.x;
	mat[1][iCol] = vec.y;
	mat[2][iCol] = vec.z;
}

Vector3 Matrix3x3::operator*(const Vector3& rhs) const {
	Vector3 prod;
	for (size_t rowIndex = 0; rowIndex < 3; rowIndex++) {
		prod[rowIndex] = mat[rowIndex][0] * rhs.x + mat[rowIndex][1] * rhs.y + mat[rowIndex][2] * rhs.z;
	}
	return prod;
}

Vector3 operator*(const Vector3& point, const Matrix3x3& rhs) {
	Vector3 prod;
	for (size_t rowIndex = 0; rowIndex < 3; rowIndex++) {
		prod[rowIndex] =
			point.x * rhs.mat[0][rowIndex] + point.y * rhs.mat[1][rowIndex] + point.z * rhs.mat[2][rowIndex];
	}
	return prod;
}

} // namespace EngineS