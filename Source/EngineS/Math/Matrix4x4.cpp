#include "Matrix4x4.hpp"
#include "Vector2.hpp"
#include "Vector3.hpp"
#include "Vector4.hpp"

#include <fmt/format.h>

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
    return Vector4(
        mat[0][0] * v.x + mat[0][1] * v.y + mat[0][2] * v.z + mat[0][3] * v.w,
        mat[1][0] * v.x + mat[1][1] * v.y + mat[1][2] * v.z + mat[1][3] * v.w,
        mat[2][0] * v.x + mat[2][1] * v.y + mat[2][2] * v.z + mat[2][3] * v.w,
        mat[3][0] * v.x + mat[3][1] * v.y + mat[3][2] * v.z + mat[3][3] * v.w
    );
}

Matrix4x4 Matrix4x4::InverseAffine() const {
    float m10 = mat[1][0], m11 = mat[1][1], m12 = mat[1][2];
    float m20 = mat[2][0], m21 = mat[2][1], m22 = mat[2][2];

    float t00 = m22 * m11 - m21 * m12;
    float t10 = m20 * m12 - m22 * m10;
    float t20 = m21 * m10 - m20 * m11;

    float m00 = mat[0][0], m01 = mat[0][1], m02 = mat[0][2];

    float invDet = 1 / (m00 * t00 + m01 * t10 + m02 * t20);

    t00 *= invDet;
    t10 *= invDet;
    t20 *= invDet;

    m00 *= invDet;
    m01 *= invDet;
    m02 *= invDet;

    float r00 = t00;
    float r01 = m02 * m21 - m01 * m22;
    float r02 = m01 * m12 - m02 * m11;

    float r10 = t10;
    float r11 = m00 * m22 - m02 * m20;
    float r12 = m02 * m10 - m00 * m12;

    float r20 = t20;
    float r21 = m01 * m20 - m00 * m21;
    float r22 = m00 * m11 - m01 * m10;

    float m03 = mat[0][3], m13 = mat[1][3], m23 = mat[2][3];

    float r03 = -(r00 * m03 + r01 * m13 + r02 * m23);
    float r13 = -(r10 * m03 + r11 * m13 + r12 * m23);
    float r23 = -(r20 * m03 + r21 * m13 + r22 * m23);

    return Matrix4x4(r00, r01, r02, r03, r10, r11, r12, r13, r20, r21, r22, r23, 0, 0, 0, 1);
}

std::string Matrix4x4::ToString() const {
    return fmt::format(
        "Matrix4x4(({}, {}, {}, {}), ({}, {}, {}, {}), ({}, {}, {}, {}), ({}, {}, {}, {})",
        mat[0][0],
        mat[0][1],
        mat[0][2],
        mat[0][3],
        mat[1][0],
        mat[1][1],
        mat[1][2],
        mat[1][3],
        mat[2][0],
        mat[2][1],
        mat[2][2],
        mat[2][3],
        mat[3][0],
        mat[3][1],
        mat[3][2],
        mat[3][3]
    );
}

} // namespace EngineS