#pragma once

#include "Core/Macros.hpp"
#include "MathDefs.hpp"

#include <cmath>
#include <iostream>
#include <string>

namespace EngineS {

class Vector3 {
  public:
    float x {0.f};
    float y {0.f};
    float z {0.f};

    static const Vector3 Back;
    static const Vector3 Down;
    static const Vector3 Forward;
    static const Vector3 Left;
    static const Vector3 NegativeInfinity;
    static const Vector3 One;
    static const Vector3 PositiveInfinity;
    static const Vector3 Right;
    static const Vector3 Up;
    static const Vector3 Zero;

  public:
    Vector3() = default;
    Vector3(float x, float y, float z) : x {x}, y {y}, z {z} {}
    explicit Vector3(float scalar) : x {scalar}, y {scalar}, z {scalar} {}

    explicit operator Vector2() const;

    float operator[](size_t i) const {
        ES_ASSERT_MSG(i < 3, "index out of range!");
        return *(&x + i);
    }
    float& operator[](size_t i) {
        ES_ASSERT_MSG(i < 3, "index out of range!");
        return *(&x + i);
    }

    float*       Data() { return &x; }
    const float* Data() const { return &x; }

    void Set(float newX, float newY, float newZ) {
        x = newX;
        y = newY;
        z = newZ;
    }

    bool operator==(const Vector3& rhs) const { return (x == rhs.x && y == rhs.y && z == rhs.z); }
    bool operator!=(const Vector3& rhs) const { return x != rhs.x || y != rhs.y || z != rhs.z; }

    Vector3 operator+(const Vector3& rhs) const { return {x + rhs.x, y + rhs.y, z + rhs.z}; }
    Vector3 operator-(const Vector3& rhs) const { return {x - rhs.x, y - rhs.y, z - rhs.z}; }
    Vector3 operator*(float scalar) const { return {x * scalar, y * scalar, z * scalar}; }
    Vector3 operator*(const Vector3& rhs) const { return {x * rhs.x, y * rhs.y, z * rhs.z}; }
    Vector3 operator/(float scalar) const {
        ES_ASSERT_MSG(scalar != 0.0f, "divided by zero!");
        return {x / scalar, y / scalar, z / scalar};
    }
    Vector3 operator/(const Vector3& rhs) const {
        ES_ASSERT_MSG((rhs.x != 0 && rhs.y != 0 && rhs.z != 0), "divided by zero!");
        return {x / rhs.x, y / rhs.y, z / rhs.z};
    }
    const Vector3& operator+() const { return *this; }
    Vector3        operator-() const { return {-x, -y, -z}; }
    friend Vector3 operator*(float scalar, const Vector3& rhs) {
        return {scalar * rhs.x, scalar * rhs.y, scalar * rhs.z};
    }

    Vector3& operator+=(const Vector3& rhs) {
        x += rhs.x;
        y += rhs.y;
        z += rhs.z;
        return *this;
    }
    Vector3& operator-=(const Vector3& rhs) {
        x -= rhs.x;
        y -= rhs.y;
        z -= rhs.z;
        return *this;
    }
    Vector3& operator*=(float scalar) {
        x *= scalar;
        y *= scalar;
        z *= scalar;
        return *this;
    }
    Vector3& operator*=(const Vector3& rhs) {
        x *= rhs.x;
        y *= rhs.y;
        z *= rhs.z;
        return *this;
    }
    Vector3& operator/=(float scalar) {
        ES_ASSERT_MSG(scalar != 0.0, "divided by zero!");
        x /= scalar;
        y /= scalar;
        z /= scalar;
        return *this;
    }
    Vector3& operator/=(const Vector3& rhs) {
        ES_ASSERT_MSG(rhs.x != 0 && rhs.y != 0 && rhs.z != 0, "divided by zero!");
        x /= rhs.x;
        y /= rhs.y;
        z /= rhs.z;
        return *this;
    }

    float   Magnitude() const { return std::hypot(x, y, z); }
    float   SqrMagnitude() const { return x * x + y * y + z * z; }
    Vector3 Normalized() const {
        Vector3 ret = *this;
        ret.Normalize();
        return ret;
    }
    void Normalize() {
        float length = Magnitude();
        if (length == 0.0f)
            return;
        float invLength = 1.0f / length;
        *this *= invLength;
    }

    static float   Distance(const Vector3& a, const Vector3& b) { return (b - a).Magnitude(); }
    static float   SqrDistance(const Vector3& a, const Vector3& b) { return (b - a).SqrMagnitude(); }
    static float   Dot(const Vector3& a, const Vector3& b) { return a.x * b.x + a.y * b.y + a.z * b.z; }
    static Vector3 Cross(const Vector3& a, const Vector3& b) {
        return {a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x};
    }
    static float Angle(const Vector3& from, const Vector3& to) {
        float lenProduct = from.Magnitude() * to.Magnitude();
        if (lenProduct < 1e-6f)
            lenProduct = 1e-6f;
        float f = Dot(from, to) / lenProduct;
        f       = Math::Clamp(f, -1.0f, 1.0f);
        return Math::Acos(f);
    }
    static Vector3 Lerp(const Vector3& lhs, const Vector3& rhs, float alpha) { return lhs + alpha * (rhs - lhs); }
    static Vector3 Reflect(const Vector3& in, const Vector3& normal) { return in - (2 * Dot(in, normal) * normal); }
    static Vector3 Clamp(const Vector3& v, const Vector3& min, const Vector3& max) {
        return {Math::Clamp(v.x, min.x, max.x), Math::Clamp(v.y, min.y, max.y), Math::Clamp(v.z, min.z, max.z)};
    }
    static Vector3 Project(const Vector3& v, const Vector3& normal) { return v - Dot(v, normal) * normal; }

    std::string ToString() const;
};

} // namespace EngineS
