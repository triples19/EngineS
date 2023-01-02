#include "Type.hpp"
#include "Base/Hash.hpp"
#include "TypeRegistry.hpp"

namespace EngineS {

Type::Type(const std::string& name, const Type* baseType) {
    Hasher<std::string> hasher;
    _hash     = hasher(name);
    _baseType = baseType;
    _name     = name;
    TypeRegistry::Instance()->RegisterType(this);
}

bool Type::Is(const std::string& name) const {
    return _hash == Hasher<std::string> {}(name);
}

bool Type::Is(const Type* type) const {
    return *this == *type;
}

bool Type::IsBaseOf(const std::string& name) const {
    auto type = TypeRegistry::Instance()->GetType(name);
    return IsBaseOf(type);
}

bool Type::IsBaseOf(const Type* type) const {
    return type->DerivedFrom(this);
}

bool Type::DerivedFrom(const std::string& name) const {
    auto type = TypeRegistry::Instance()->GetType(name);
    return DerivedFrom(type);
}

bool Type::DerivedFrom(const Type* type) const {
    if (*this == *type)
        return true;
    if (_baseType == nullptr)
        return false;
    return _baseType->IsBaseOf(type);
}

} // namespace EngineS