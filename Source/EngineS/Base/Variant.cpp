#include "Base/Variant.hpp"
#include "Reflection/Type.hpp"

namespace EngineS {

Variant::Variant() : _type(VariantType::None) {
    std::memset(_val._buffer, 0, sizeof(_val._buffer));
}

Variant::~Variant() {
    Release();
}

Variant& Variant::operator=(const Variant& rhs) {
    SetType(rhs._type);

    switch (_type) {
        case VariantType::Vector2:
            *_val._vector2 = *rhs._val._vector2;
            break;
        case VariantType::Vector3:
            *_val._vector3 = *rhs._val._vector3;
            break;
        case VariantType::Vector4:
            *_val._vector4 = *rhs._val._vector4;
            break;
        case VariantType::String:
            *_val._string = *rhs._val._string;
            break;
        case VariantType::Matrix3x3:
            *_val._matrix3x3 = *rhs._val._matrix3x3;
            break;
        case VariantType::Matrix4x4:
            *_val._matrix4x4 = *rhs._val._matrix4x4;
            break;
        default:
            std::memcpy(&_val, &rhs._val, sizeof(VariantValue));
            break;
    }

    return *this;
}

void Variant::SetType(VariantType type) {
    if (_type == type)
        return;

    Release();

    _type = type;

    switch (type) {
        case VariantType::None:
            break;
        case VariantType::Object:
            break;
        case VariantType::Int:
            break;
        case VariantType::Bool:
            break;
        case VariantType::Float:
            break;
        case VariantType::Double:
            break;
        case VariantType::Vector2:
            _val._vector2 = new Vector2;
            break;
        case VariantType::Vector3:
            _val._vector3 = new Vector3;
            break;
        case VariantType::Vector4:
            _val._vector4 = new Vector4;
            break;
        case VariantType::String:
            _val._string = new std::string;
            break;
        case VariantType::Matrix3x3:
            _val._matrix3x3 = new Matrix3x3;
            break;
        case VariantType::Matrix4x4:
            _val._matrix4x4 = new Matrix4x4;
            break;
    }
}

void Variant::Release() {
    switch (_type) {
        case VariantType::None:
            break;
        case VariantType::Object:
            break;
        case VariantType::Int:
            break;
        case VariantType::Bool:
            break;
        case VariantType::Float:
            break;
        case VariantType::Double:
            break;
        case VariantType::Vector2:
            delete _val._vector2;
            break;
        case VariantType::Vector3:
            delete _val._vector3;
            break;
        case VariantType::Vector4:
            delete _val._vector4;
            break;
        case VariantType::String:
            delete _val._string;
            break;
        case VariantType::Matrix3x3:
            delete _val._matrix3x3;
            break;
        case VariantType::Matrix4x4:
            delete _val._matrix4x4;
            break;
    }
}

std::string Variant::ToString() const {
    switch (_type) {
        case VariantType::None:
            return "Variant::None";
        case VariantType::Object:
            return static_cast<std::string>(_val._object->GetType()->GetName());
        case VariantType::Int:
            return std::to_string(_val._int);
        case VariantType::Bool:
            return _val._bool ? "true" : "false";
        case VariantType::Float:
            return std::to_string(_val._float);
        case VariantType::Double:
            return std::to_string(_val._double);
        case VariantType::Vector2:
            return _val._vector2->ToString();
        case VariantType::Vector3:
            return _val._vector3->ToString();
        case VariantType::Vector4:
            return _val._vector4->ToString();
        case VariantType::String:
            return *_val._string;
        case VariantType::Matrix3x3:
            return _val._matrix3x3->ToString();
        case VariantType::Matrix4x4:
            return _val._matrix4x4->ToString();
    }
    return "";
}

const Type* Variant::GetType() const {
    switch (_type) {
        case VariantType::None:
            break;
        case VariantType::Object:
            return _val._object->GetType();
        case VariantType::Int:
            return TypeOf<int>();
        case VariantType::Bool:
            return TypeOf<bool>();
        case VariantType::Float:
            return TypeOf<float>();
        case VariantType::Double:
            return TypeOf<double>();
        case VariantType::Vector2:
            break;
        case VariantType::Vector3:
            break;
        case VariantType::Vector4:
            break;
        case VariantType::String:
            break;
        case VariantType::Matrix3x3:
            break;
        case VariantType::Matrix4x4:
            break;
    }
    return nullptr;
}

} // namespace EngineS