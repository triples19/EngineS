#pragma once

#include "Math.hpp"
#include <cassert>
#include <cmath>

namespace EngineS {

class Matrix4x4 {
  public:
	float mat[4][4];

	static const Matrix4x4 Identity;
	static const Matrix4x4 Zero;

  public:
	Matrix4x4() { *this = Identity; }

	Matrix4x4(const float (&arr)[16]) {
		mat[0][0] = arr[0];
		mat[0][1] = arr[1];
		mat[0][2] = arr[2];
		mat[0][3] = arr[3];
		mat[1][0] = arr[4];
		mat[1][1] = arr[5];
		mat[1][2] = arr[6];
		mat[1][3] = arr[7];
		mat[2][0] = arr[8];
		mat[2][1] = arr[9];
		mat[2][2] = arr[10];
		mat[2][3] = arr[11];
		mat[3][0] = arr[12];
		mat[3][1] = arr[13];
		mat[3][2] = arr[14];
		mat[3][3] = arr[15];
	}

	Matrix4x4(float m00,
			  float m01,
			  float m02,
			  float m03,
			  float m10,
			  float m11,
			  float m12,
			  float m13,
			  float m20,
			  float m21,
			  float m22,
			  float m23,
			  float m30,
			  float m31,
			  float m32,
			  float m33) {
		mat[0][0] = m00;
		mat[0][1] = m01;
		mat[0][2] = m02;
		mat[0][3] = m03;
		mat[1][0] = m10;
		mat[1][1] = m11;
		mat[1][2] = m12;
		mat[1][3] = m13;
		mat[2][0] = m20;
		mat[2][1] = m21;
		mat[2][2] = m22;
		mat[2][3] = m23;
		mat[3][0] = m30;
		mat[3][1] = m31;
		mat[3][2] = m32;
		mat[3][3] = m33;
	}

	Matrix4x4(const Vector4& row0, const Vector4& row1, const Vector4& row2, const Vector4& row3);

	const float* Data() const { return &mat[0][0]; }

	float* operator[](size_t rowIndex) const { return const_cast<float*>(mat[rowIndex]); }

	Matrix4x4 Concatenate(const Matrix4x4& m2) const {
		Matrix4x4 r;
		r.mat[0][0] =
			mat[0][0] * m2.mat[0][0] + mat[0][1] * m2.mat[1][0] + mat[0][2] * m2.mat[2][0] + mat[0][3] * m2.mat[3][0];
		r.mat[0][1] =
			mat[0][0] * m2.mat[0][1] + mat[0][1] * m2.mat[1][1] + mat[0][2] * m2.mat[2][1] + mat[0][3] * m2.mat[3][1];
		r.mat[0][2] =
			mat[0][0] * m2.mat[0][2] + mat[0][1] * m2.mat[1][2] + mat[0][2] * m2.mat[2][2] + mat[0][3] * m2.mat[3][2];
		r.mat[0][3] =
			mat[0][0] * m2.mat[0][3] + mat[0][1] * m2.mat[1][3] + mat[0][2] * m2.mat[2][3] + mat[0][3] * m2.mat[3][3];

		r.mat[1][0] =
			mat[1][0] * m2.mat[0][0] + mat[1][1] * m2.mat[1][0] + mat[1][2] * m2.mat[2][0] + mat[1][3] * m2.mat[3][0];
		r.mat[1][1] =
			mat[1][0] * m2.mat[0][1] + mat[1][1] * m2.mat[1][1] + mat[1][2] * m2.mat[2][1] + mat[1][3] * m2.mat[3][1];
		r.mat[1][2] =
			mat[1][0] * m2.mat[0][2] + mat[1][1] * m2.mat[1][2] + mat[1][2] * m2.mat[2][2] + mat[1][3] * m2.mat[3][2];
		r.mat[1][3] =
			mat[1][0] * m2.mat[0][3] + mat[1][1] * m2.mat[1][3] + mat[1][2] * m2.mat[2][3] + mat[1][3] * m2.mat[3][3];

		r.mat[2][0] =
			mat[2][0] * m2.mat[0][0] + mat[2][1] * m2.mat[1][0] + mat[2][2] * m2.mat[2][0] + mat[2][3] * m2.mat[3][0];
		r.mat[2][1] =
			mat[2][0] * m2.mat[0][1] + mat[2][1] * m2.mat[1][1] + mat[2][2] * m2.mat[2][1] + mat[2][3] * m2.mat[3][1];
		r.mat[2][2] =
			mat[2][0] * m2.mat[0][2] + mat[2][1] * m2.mat[1][2] + mat[2][2] * m2.mat[2][2] + mat[2][3] * m2.mat[3][2];
		r.mat[2][3] =
			mat[2][0] * m2.mat[0][3] + mat[2][1] * m2.mat[1][3] + mat[2][2] * m2.mat[2][3] + mat[2][3] * m2.mat[3][3];

		r.mat[3][0] =
			mat[3][0] * m2.mat[0][0] + mat[3][1] * m2.mat[1][0] + mat[3][2] * m2.mat[2][0] + mat[3][3] * m2.mat[3][0];
		r.mat[3][1] =
			mat[3][0] * m2.mat[0][1] + mat[3][1] * m2.mat[1][1] + mat[3][2] * m2.mat[2][1] + mat[3][3] * m2.mat[3][1];
		r.mat[3][2] =
			mat[3][0] * m2.mat[0][2] + mat[3][1] * m2.mat[1][2] + mat[3][2] * m2.mat[2][2] + mat[3][3] * m2.mat[3][2];
		r.mat[3][3] =
			mat[3][0] * m2.mat[0][3] + mat[3][1] * m2.mat[1][3] + mat[3][2] * m2.mat[2][3] + mat[3][3] * m2.mat[3][3];

		return r;
	}

	Matrix4x4 operator*(const Matrix4x4& m2) const { return Concatenate(m2); }
	Vector4	  operator*(const Vector4& v) const;

	Matrix4x4 operator+(const Matrix4x4& m2) const {
		Matrix4x4 r;

		r.mat[0][0] = mat[0][0] + m2.mat[0][0];
		r.mat[0][1] = mat[0][1] + m2.mat[0][1];
		r.mat[0][2] = mat[0][2] + m2.mat[0][2];
		r.mat[0][3] = mat[0][3] + m2.mat[0][3];

		r.mat[1][0] = mat[1][0] + m2.mat[1][0];
		r.mat[1][1] = mat[1][1] + m2.mat[1][1];
		r.mat[1][2] = mat[1][2] + m2.mat[1][2];
		r.mat[1][3] = mat[1][3] + m2.mat[1][3];

		r.mat[2][0] = mat[2][0] + m2.mat[2][0];
		r.mat[2][1] = mat[2][1] + m2.mat[2][1];
		r.mat[2][2] = mat[2][2] + m2.mat[2][2];
		r.mat[2][3] = mat[2][3] + m2.mat[2][3];

		r.mat[3][0] = mat[3][0] + m2.mat[3][0];
		r.mat[3][1] = mat[3][1] + m2.mat[3][1];
		r.mat[3][2] = mat[3][2] + m2.mat[3][2];
		r.mat[3][3] = mat[3][3] + m2.mat[3][3];

		return r;
	}

	Matrix4x4 operator-(const Matrix4x4& m2) const {
		Matrix4x4 r;
		r.mat[0][0] = mat[0][0] - m2.mat[0][0];
		r.mat[0][1] = mat[0][1] - m2.mat[0][1];
		r.mat[0][2] = mat[0][2] - m2.mat[0][2];
		r.mat[0][3] = mat[0][3] - m2.mat[0][3];

		r.mat[1][0] = mat[1][0] - m2.mat[1][0];
		r.mat[1][1] = mat[1][1] - m2.mat[1][1];
		r.mat[1][2] = mat[1][2] - m2.mat[1][2];
		r.mat[1][3] = mat[1][3] - m2.mat[1][3];

		r.mat[2][0] = mat[2][0] - m2.mat[2][0];
		r.mat[2][1] = mat[2][1] - m2.mat[2][1];
		r.mat[2][2] = mat[2][2] - m2.mat[2][2];
		r.mat[2][3] = mat[2][3] - m2.mat[2][3];

		r.mat[3][0] = mat[3][0] - m2.mat[3][0];
		r.mat[3][1] = mat[3][1] - m2.mat[3][1];
		r.mat[3][2] = mat[3][2] - m2.mat[3][2];
		r.mat[3][3] = mat[3][3] - m2.mat[3][3];

		return r;
	}

	Matrix4x4 operator*(float scalar) const {
		return Matrix4x4(scalar * mat[0][0],
						 scalar * mat[0][1],
						 scalar * mat[0][2],
						 scalar * mat[0][3],
						 scalar * mat[1][0],
						 scalar * mat[1][1],
						 scalar * mat[1][2],
						 scalar * mat[1][3],
						 scalar * mat[2][0],
						 scalar * mat[2][1],
						 scalar * mat[2][2],
						 scalar * mat[2][3],
						 scalar * mat[3][0],
						 scalar * mat[3][1],
						 scalar * mat[3][2],
						 scalar * mat[3][3]);
	}

	bool operator==(const Matrix4x4& m2) const {
		return !(mat[0][0] != m2.mat[0][0] || mat[0][1] != m2.mat[0][1] || mat[0][2] != m2.mat[0][2] ||
				 mat[0][3] != m2.mat[0][3] || mat[1][0] != m2.mat[1][0] || mat[1][1] != m2.mat[1][1] ||
				 mat[1][2] != m2.mat[1][2] || mat[1][3] != m2.mat[1][3] || mat[2][0] != m2.mat[2][0] ||
				 mat[2][1] != m2.mat[2][1] || mat[2][2] != m2.mat[2][2] || mat[2][3] != m2.mat[2][3] ||
				 mat[3][0] != m2.mat[3][0] || mat[3][1] != m2.mat[3][1] || mat[3][2] != m2.mat[3][2] ||
				 mat[3][3] != m2.mat[3][3]);
	}

	bool operator!=(const Matrix4x4& m2) const {
		return mat[0][0] != m2.mat[0][0] || mat[0][1] != m2.mat[0][1] || mat[0][2] != m2.mat[0][2] ||
			   mat[0][3] != m2.mat[0][3] || mat[1][0] != m2.mat[1][0] || mat[1][1] != m2.mat[1][1] ||
			   mat[1][2] != m2.mat[1][2] || mat[1][3] != m2.mat[1][3] || mat[2][0] != m2.mat[2][0] ||
			   mat[2][1] != m2.mat[2][1] || mat[2][2] != m2.mat[2][2] || mat[2][3] != m2.mat[2][3] ||
			   mat[3][0] != m2.mat[3][0] || mat[3][1] != m2.mat[3][1] || mat[3][2] != m2.mat[3][2] ||
			   mat[3][3] != m2.mat[3][3];
	}

	Matrix4x4 Transposed() const {
		return Matrix4x4(mat[0][0],
						 mat[1][0],
						 mat[2][0],
						 mat[3][0],
						 mat[0][1],
						 mat[1][1],
						 mat[2][1],
						 mat[3][1],
						 mat[0][2],
						 mat[1][2],
						 mat[2][2],
						 mat[3][2],
						 mat[0][3],
						 mat[1][3],
						 mat[2][3],
						 mat[3][3]);
	}

	float Minor(size_t r0, size_t r1, size_t r2, size_t c0, size_t c1, size_t c2) const {
		return mat[r0][c0] * (mat[r1][c1] * mat[r2][c2] - mat[r2][c1] * mat[r1][c2]) -
			   mat[r0][c1] * (mat[r1][c0] * mat[r2][c2] - mat[r2][c0] * mat[r1][c2]) +
			   mat[r0][c2] * (mat[r1][c0] * mat[r2][c1] - mat[r2][c0] * mat[r1][c1]);
	}

	float Determinant() const {
		return mat[0][0] * Minor(1, 2, 3, 1, 2, 3) - mat[0][1] * Minor(1, 2, 3, 0, 2, 3) +
			   mat[0][2] * Minor(1, 2, 3, 0, 1, 3) - mat[0][3] * Minor(1, 2, 3, 0, 1, 2);
	}

	bool	  IsAffine() const { return mat[3][0] == 0 && mat[3][1] == 0 && mat[3][2] == 0 && mat[3][3] == 1; }
	Matrix4x4 InverseAffine() const;
};

} // namespace EngineS