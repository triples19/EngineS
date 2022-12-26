#pragma once

#include "Base/PrimitiveTypes.hpp"

#include <string>

namespace EngineS {

class Object;

class Type {
  public:
    virtual Object*    CreateObject() const;
    const std::string& GetTypeName() const;
    hash32             GetHashValue() const;

    friend auto operator<=>(const Type& lhs, const Type& rhs);

  private:
    hash32      _hash;
    const Type* _baseType;
};

template<class T>
class TypeImpl : public Type {
  public:
    virtual Object* CreateObject() const { return T::Create(); }
};

} // namespace EngineS

template<>
struct std::hash<EngineS::Type> {
    std::size_t operator()(const EngineS::Type& type) { return type.GetHashValue(); }
};