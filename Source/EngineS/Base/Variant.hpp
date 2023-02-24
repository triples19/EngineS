#pragma once

#include "Base/Concepts.hpp"
#include "Base/PrimitiveTypes.hpp"
#include "Math/Math.hpp"

#include <string>

namespace EngineS {

enum class VariantType : u32 {
    None,
    Object,
    Int,
    Bool,
    Float,
    Double,
    Vector2,
    Vector3,
    Vector4,
    String,
    Matrix3x3,
    Matrix4x4,
};

union VariantValue {
    byte         _buffer[8];
    Object*      _object;
    int          _int;
    bool         _bool;
    float        _float;
    double       _double;
    Vector2*     _vector2;
    Vector3*     _vector3;
    Vector4*     _vector4;
    std::string* _string;
    Matrix3x3*   _matrix3x3;
    Matrix4x4*   _matrix4x4;
};

class Variant {
  public:
    Variant();
    ~Variant();

    Variant(const Variant& rhs) { *this = rhs; }

    Variant& operator=(const Variant& rhs);

    Variant(Object* val) { *this = val; }
    Variant(int val) { *this = val; }
    Variant(bool val) { *this = val; }
    Variant(float val) { *this = val; }
    Variant(double val) { *this = val; }
    Variant(const Vector2& val) { *this = val; }
    Variant(const Vector3& val) { *this = val; }
    Variant(const Vector4& val) { *this = val; }
    Variant(const std::string& val) { *this = val; }
    Variant(const Matrix3x3& val) { *this = val; }
    Variant(const Matrix4x4& val) { *this = val; }

    Variant& operator=(Object* val) {
        SetType(VariantType::Object);
        _val._object = val;
        return *this;
    }

    Variant& operator=(int val) {
        SetType(VariantType::Int);
        _val._int = val;
        return *this;
    }

    Variant& operator=(bool val) {
        SetType(VariantType::Bool);
        _val._bool = val;
        return *this;
    }

    Variant& operator=(float val) {
        SetType(VariantType::Float);
        _val._float = val;
        return *this;
    }

    Variant& operator=(double val) {
        SetType(VariantType::Double);
        _val._double = val;
        return *this;
    }

    Variant& operator=(const Vector2& val) {
        SetType(VariantType::Vector2);
        *_val._vector2 = val;
        return *this;
    }

    Variant& operator=(const Vector3& val) {
        SetType(VariantType::Vector3);
        *_val._vector3 = val;
        return *this;
    }

    Variant& operator=(const Vector4& val) {
        SetType(VariantType::Vector4);
        *_val._vector4 = val;
        return *this;
    }

    Variant& operator=(const std::string& val) {
        SetType(VariantType::String);
        *_val._string = val;
        return *this;
    }

    Variant& operator=(const Matrix3x3& val) {
        SetType(VariantType::Matrix3x3);
        *_val._matrix3x3 = val;
        return *this;
    }

    Variant& operator=(const Matrix4x4& val) {
        SetType(VariantType::Matrix4x4);
        *_val._matrix4x4 = val;
        return *this;
    }

    VariantType GetVariantType() const { return _type; }

    const Type* GetType() const;

    i32 GetI32() const {
        if (_type == VariantType::Int) {
            return _val._int;
        } else if (_type == VariantType::Float) {
            return static_cast<i32>(_val._float);
        } else if (_type == VariantType::Double) {
            return static_cast<i32>(_val._double);
        } else {
            return 0;
        }
    }

    explicit operator i32() const { return GetI32(); }

    bool GetBool() const {
        if (_type == VariantType::Bool) {
            return _val._bool;
        } else {
            return false;
        }
    }

    explicit operator bool() const { return GetBool(); }

    float GetFloat() const {
        if (_type == VariantType::Float) {
            return _val._float;
        } else if (_type == VariantType::Double) {
            return static_cast<float>(_val._double);
        } else if (_type == VariantType::Int) {
            return static_cast<float>(_val._int);
        } else {
            return 0.0f;
        }
    }

    explicit operator float() const { return GetFloat(); }

    double GetDouble() const {
        if (_type == VariantType::Double) {
            return _val._double;
        } else if (_type == VariantType::Float) {
            return static_cast<double>(_val._float);
        } else if (_type == VariantType::Int) {
            return static_cast<double>(_val._int);
        } else {
            return 0.0;
        }
    }

    explicit operator double() const { return GetDouble(); }

    template<IsObject T = Object>
    T* GetObject() const {
        if (_type == VariantType::Object) {
            return static_cast<T*>(_val._object);
        } else {
            return nullptr;
        }
    }

    template<IsObject T>
    explicit operator T*() const {
        return GetObject<T>();
    }

    Vector2 GetVector2() const {
        if (_type == VariantType::Vector2) {
            return *_val._vector2;
        } else {
            return Vector2::Zero;
        }
    }

    explicit operator Vector2() const { return GetVector2(); }

    Vector3 GetVector3() const {
        if (_type == VariantType::Vector3) {
            return *_val._vector3;
        } else {
            return Vector3::Zero;
        }
    }

    explicit operator Vector3() const { return GetVector3(); }

    Vector4 GetVector4() const {
        if (_type == VariantType::Vector4) {
            return *_val._vector4;
        } else {
            return Vector4::Zero;
        }
    }

    explicit operator Vector4() const { return GetVector4(); }

    Matrix3x3 GetMatrix3x3() const {
        if (_type == VariantType::Matrix3x3) {
            return *_val._matrix3x3;
        } else {
            return Matrix3x3::Zero;
        }
    }

    explicit operator Matrix3x3() const { return GetMatrix3x3(); }

    Matrix4x4 GetMatrix4x4() const {
        if (_type == VariantType::Matrix4x4) {
            return *_val._matrix4x4;
        } else {
            return Matrix4x4::Zero;
        }
    }

    explicit operator Matrix4x4() const { return GetMatrix4x4(); }

    std::string GetString() const { return ToString(); }

    explicit operator std::string() const { return GetString(); }

    std::string ToString() const;

    friend std::ostream& operator<<(std::ostream& os, const Variant& v) {
        os << v.ToString();
        return os;
    }

  private:
    void SetType(VariantType type);
    void Release();

  private:
    VariantType  _type;
    VariantValue _val;
};

} // namespace EngineS

#include <fmt/ostream.h>
template<>
struct fmt::formatter<EngineS::Variant> : fmt::ostream_formatter {};