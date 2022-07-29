#pragma once

#include "Math.hpp"
#include <cstring>

namespace EngineS {

class Matrix3x3 {
  public:
	float mat[3][3];

	static const Matrix3x3 Identity;
	static const Matrix3x3 Zero;

  public:
	Matrix3x3() { *this = Identity; }

	explicit Matrix3x3(float arr[3][3]) {
		memcpy(mat[0], arr[0], 3 * sizeof(float));
		memcpy(mat[1], arr[1], 3 * sizeof(float));
		memcpy(mat[2], arr[2], 3 * sizeof(float));
	}

	explicit Matrix3x3(float (&arr)[9]) {
		mat[0][0] = arr[0];
		mat[0][1] = arr[1];
		mat[0][2] = arr[2];
		mat[1][0] = arr[3];
		mat[1][1] = arr[4];
		mat[1][2] = arr[5];
		mat[2][0] = arr[6];
		mat[2][1] = arr[7];
		mat[2][2] = arr[8];
	}

	Matrix3x3(float entry00,
			  float entry01,
			  float entry02,
			  float entry10,
			  float entry11,
			  float entry12,
			  float entry20,
			  float entry21,
			  float entry22) {
		mat[0][0] = entry00;
		mat[0][1] = entry01;
		mat[0][2] = entry02;
		mat[1][0] = entry10;
		mat[1][1] = entry11;
		mat[1][2] = entry12;
		mat[2][0] = entry20;
		mat[2][1] = entry21;
		mat[2][2] = entry22;
	}

	Matrix3x3(const Vector3& row0, const Vector3& row1, const Vector3& row2);

	const float* Data() const { return &mat[0][0]; }

	float* operator[](size_t rowIndex) const { return const_cast<float*>(mat[rowIndex]); }

	Vector3 GetColumn(size_t iCol) const;
	void	SetColumn(size_t iCol, const Vector3& vec);

	bool operator==(const Matrix3x3& rhs) const {
		for (size_t rowIndex = 0; rowIndex < 3; rowIndex++) {
			for (size_t colIndex = 0; colIndex < 3; colIndex++) {
				if (mat[rowIndex][colIndex] != rhs.mat[rowIndex][colIndex])
					return false;
			}
		}
		return true;
	}
	bool operator!=(const Matrix3x3& rhs) const { return !operator==(rhs); }

	Matrix3x3 operator+(const Matrix3x3& rhs) const {
		Matrix3x3 sum;
		for (size_t rowIndex = 0; rowIndex < 3; rowIndex++) {
			for (size_t colIndex = 0; colIndex < 3; colIndex++) {
				sum.mat[rowIndex][colIndex] = mat[rowIndex][colIndex] + rhs.mat[rowIndex][colIndex];
			}
		}
		return sum;
	}

	Matrix3x3 operator-(const Matrix3x3& rhs) const {
		Matrix3x3 diff;
		for (size_t rowIndex = 0; rowIndex < 3; rowIndex++) {
			for (size_t colIndex = 0; colIndex < 3; colIndex++) {
				diff.mat[rowIndex][colIndex] = mat[rowIndex][colIndex] - rhs.mat[rowIndex][colIndex];
			}
		}
		return diff;
	}

	Matrix3x3 operator*(const Matrix3x3& rhs) const {
		Matrix3x3 prod;
		for (size_t rowIndex = 0; rowIndex < 3; rowIndex++) {
			for (size_t colIndex = 0; colIndex < 3; colIndex++) {
				prod.mat[rowIndex][colIndex] = mat[rowIndex][0] * rhs.mat[0][colIndex] +
											   mat[rowIndex][1] * rhs.mat[1][colIndex] +
											   mat[rowIndex][2] * rhs.mat[2][colIndex];
			}
		}
		return prod;
	}

	// matrix * vector [3x3 * 3x1 = 3x1]
	Vector3 operator*(const Vector3& rhs) const;

	// vector * matrix [1x3 * 3x3 = 1x3]
	friend Vector3 operator*(const Vector3& point, const Matrix3x3& rhs);

	Matrix3x3 operator-() const {
		Matrix3x3 neg;
		for (size_t rowIndex = 0; rowIndex < 3; rowIndex++) {
			for (size_t colIndex = 0; colIndex < 3; colIndex++) neg[rowIndex][colIndex] = -mat[rowIndex][colIndex];
		}
		return neg;
	}

	// matrix * scalar
	Matrix3x3 operator*(float scalar) const {
		Matrix3x3 prod;
		for (size_t rowIndex = 0; rowIndex < 3; rowIndex++) {
			for (size_t colIndex = 0; colIndex < 3; colIndex++)
				prod[rowIndex][colIndex] = scalar * mat[rowIndex][colIndex];
		}
		return prod;
	}

	// scalar * matrix
	friend Matrix3x3 operator*(float scalar, const Matrix3x3& rhs) {
		Matrix3x3 prod;
		for (size_t rowIndex = 0; rowIndex < 3; rowIndex++) {
			for (size_t colIndex = 0; colIndex < 3; colIndex++)
				prod[rowIndex][colIndex] = scalar * rhs.mat[rowIndex][colIndex];
		}
		return prod;
	}

	Matrix3x3 Transposed() const {
		Matrix3x3 ret;
		for (size_t rowIndex = 0; rowIndex < 3; rowIndex++) {
			for (size_t colIndex = 0; colIndex < 3; colIndex++) {
				ret[rowIndex][colIndex] = mat[colIndex][rowIndex];
			}
		}
		return ret;
	}

	float Determinant() const {
		float cofactor00 = mat[1][1] * mat[2][2] - mat[1][2] * mat[2][1];
		float cofactor10 = mat[1][2] * mat[2][0] - mat[1][0] * mat[2][2];
		float cofactor20 = mat[1][0] * mat[2][1] - mat[1][1] * mat[2][0];

		float det = mat[0][0] * cofactor00 + mat[0][1] * cofactor10 + mat[0][2] * cofactor20;

		return det;
	}

	Matrix3x3 Inversed(float tolerance = 1e-06) const {
		Matrix3x3 invMat;
		float	  det = Determinant();
		if (Math::Abs(det) < tolerance)
			return Zero;

		invMat[0][0] = mat[1][1] * mat[2][2] - mat[1][2] * mat[2][1];
		invMat[0][1] = mat[0][2] * mat[2][1] - mat[0][1] * mat[2][2];
		invMat[0][2] = mat[0][1] * mat[1][2] - mat[0][2] * mat[1][1];
		invMat[1][0] = mat[1][2] * mat[2][0] - mat[1][0] * mat[2][2];
		invMat[1][1] = mat[0][0] * mat[2][2] - mat[0][2] * mat[2][0];
		invMat[1][2] = mat[0][2] * mat[1][0] - mat[0][0] * mat[1][2];
		invMat[2][0] = mat[1][0] * mat[2][1] - mat[1][1] * mat[2][0];
		invMat[2][1] = mat[0][1] * mat[2][0] - mat[0][0] * mat[2][1];
		invMat[2][2] = mat[0][0] * mat[1][1] - mat[0][1] * mat[1][0];

		float invDet = 1.0f / det;
		for (size_t rowIndex = 0; rowIndex < 3; rowIndex++) {
			for (size_t colIndex = 0; colIndex < 3; colIndex++) {
				invMat[rowIndex][colIndex] *= invDet;
			}
		}

		return invMat;
	}
};

} // namespace EngineS