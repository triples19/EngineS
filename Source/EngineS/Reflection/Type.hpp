#pragma once

#include "Base/Concepts.hpp"
#include "Base/PrimitiveTypes.hpp"

#include <string>
#include <string_view>
#include <unordered_map>

namespace EngineS {

class Object;
class MemberInfo;
class FieldInfo;
class MethodInfo;
namespace Registration {
template<class>
class Class;
}

class Type {
    template<class>
    friend class Registration::Class;

  protected:
    Type(std::string_view name, const Type* baseType);

  public:
    virtual Object*  CreateObject() const { return nullptr; }
    std::string_view GetName() const { return _name; }
    hash32           GetHashValue() const { return _hash; }

    bool Is(std::string_view name) const;
    bool Is(const Type* type) const;

    template<class T>
    bool Is() const;

    bool IsBaseOf(std::string_view name) const;
    bool IsBaseOf(const Type* type) const;

    template<class T>
    bool IsBaseOf() const;

    bool DerivedFrom(std::string_view name) const;
    bool DerivedFrom(const Type* type) const;

    template<class T>
    bool DerivedFrom() const;

    friend bool operator==(const Type& lhs, const Type& rhs) { return lhs._hash == rhs._hash; }

    std::vector<const FieldInfo*> GetFields() const;

    const FieldInfo* GetField(std::string_view name) const;

    std::vector<const MethodInfo*> GetMethods() const;

    std::vector<const MethodInfo*> GetMethods(std::string_view name) const;

  private:
    hash32           _hash;
    const Type*      _baseType;
    std::string_view _name;

    std::unordered_map<hash32, const FieldInfo*>       _fields;
    std::unordered_multimap<hash32, const MethodInfo*> _methods;
};

namespace Detail {

template<class T>
class TypeImpl : public Type {
  public:
    TypeImpl(std::string_view name, const Type* baseType) : Type(name, baseType) {}
    virtual Object* CreateObject() const { return nullptr; }
};

template<class T>
    requires DerivedFrom<T, Object> && DefaultInitializable<T>
class TypeImpl<T> : public Type {
  public:
    TypeImpl(std::string_view name, const Type* baseType) : Type(name, baseType) {}
    virtual Object* CreateObject() const { return new T; }
};

} // namespace Detail

} // namespace EngineS

#include "Reflection/TypeOf.hpp"

namespace EngineS {

template<class T>
bool Type::Is() const {
    return Is(T::GetTypeStatic());
}

template<class T>
bool Type::IsBaseOf() const {
    return IsBaseOf(T::GetTypeStatic());
}

template<class T>
bool Type::DerivedFrom() const {
    return DerivedFrom(T::GetTypeStatic());
}

} // namespace EngineS

template<>
struct std::hash<EngineS::Type> {
    std::size_t operator()(const EngineS::Type& type) { return type.GetHashValue(); }
};