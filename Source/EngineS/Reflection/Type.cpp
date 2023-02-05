#include "Type.hpp"
#include "Base/Hash.hpp"
#include "TypeRegistry.hpp"

namespace EngineS {

Type::Type(std::string_view name, const Type* baseType) {
    Hasher<std::string_view> hasher;
    _hash     = hasher(name);
    _baseType = baseType;
    _name     = name;
}

bool Type::Is(std::string_view name) const {
    return _hash == Hasher<std::string_view> {}(name);
}

bool Type::Is(const Type* type) const {
    return *this == *type;
}

bool Type::IsBaseOf(std::string_view name) const {
    auto type = TypeRegistry::Instance()->GetType(name);
    return IsBaseOf(type);
}

bool Type::IsBaseOf(const Type* type) const {
    return type->DerivedFrom(this);
}

bool Type::DerivedFrom(std::string_view name) const {
    auto type = TypeRegistry::Instance()->GetType(name);
    return DerivedFrom(type);
}

bool Type::DerivedFrom(const Type* type) const {
    if (*this == *type)
        return true;
    if (_baseType == nullptr)
        return false;
    return _baseType->DerivedFrom(type);
}

std::vector<const FieldInfo*> Type::GetFields() const {
    std::vector<const FieldInfo*> ret;
    for (auto iter = _fields.begin(); iter != _fields.end(); ++iter) {
        ret.push_back(iter->second);
    }
    return ret;
}

const FieldInfo* Type::GetField(std::string_view name) const {
    auto hash = Hasher<std::string_view> {}(name);
    auto iter = _fields.find(hash);
    if (iter == _fields.end()) {
        return nullptr;
    }
    return iter->second;
}

std::vector<const MethodInfo*> Type::GetMethods() const {
    std::vector<const MethodInfo*> ret;
    for (auto iter = _methods.begin(); iter != _methods.end(); ++iter) {
        ret.push_back(iter->second);
    }
    return ret;
}

std::vector<const MethodInfo*> Type::GetMethods(std::string_view name) const {
    auto hash         = Hasher<std::string_view> {}(name);
    auto [begin, end] = _methods.equal_range(hash);
    std::vector<const MethodInfo*> ret;
    for (auto iter = begin; iter != end; ++iter) {
        ret.push_back(iter->second);
    }
    return ret;
}

} // namespace EngineS