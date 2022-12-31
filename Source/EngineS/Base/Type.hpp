#pragma once

#include "Base/Concepts.hpp"
#include "Base/PrimitiveTypes.hpp"

#include <string>
#include <string_view>

namespace EngineS {

class Object;

class Type {
  protected:
    Type(const std::string& name, const Type* baseType);

  public:
    virtual Object*    CreateObject() const { return nullptr; }
    const std::string& GetName() const { return _name; }
    hash32             GetHashValue() const { return _hash; }

    bool Is(const std::string& name) const;
    bool Is(const Type* type) const;

    template<class T>
    bool Is() const {
        return Is(T::GetType());
    }

    bool IsBaseOf(const std::string& name) const;
    bool IsBaseOf(const Type* type) const;

    template<class T>
    bool IsBaseOf() const {
        return IsBaseOf(T::GetType());
    }

    bool DerivedFrom(const std::string& name) const;
    bool DerivedFrom(const Type* type) const;

    template<class T>
    bool DerivedFrom() const {
        return DerivedFrom(T::GetType());
    }

    friend bool operator==(const Type& lhs, const Type& rhs) { return lhs._hash == rhs._hash; }

  private:
    hash32      _hash;
    const Type* _baseType;
    std::string _name;
};

namespace Detail {

template<class T>
class TypeImpl : public Type {
  public:
    TypeImpl(const std::string& name, const Type* baseType) : Type(name, baseType) {}
    virtual Object* CreateObject() const { return new T; }
};

} // namespace Detail

} // namespace EngineS

template<>
struct std::hash<EngineS::Type> {
    std::size_t operator()(const EngineS::Type& type) { return type.GetHashValue(); }
};