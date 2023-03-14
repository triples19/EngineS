#pragma once

#include "Base/Concepts.hpp"
#include "Base/PrimitiveTypes.hpp"

#include <concepts>
#include <string>
#include <string_view>
#include <typeindex>
#include <unordered_map>
#include <vector>

namespace EngineS {

namespace Detail {
struct BaseInfo;
}

namespace Registration {
template<class>
class Class;
}

class MemberInfo;
class FieldInfo;
class MethodInfo;
class ConstructorInfo;
class DestructorInfo;

class Type {
    template<class>
    friend class Registration::Class;
    friend class TypeRegistry;

  protected:
    Type(std::string_view name, std::type_index typeIndex);

  public:
    virtual ~Type();
    std::string_view GetName() const { return _name; }
    hash32           GetHashValue() const { return _hash; }
    std::type_index  GetTypeIndex() const { return _typeIndex; }

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

    virtual void* Cast(void* ptr) const = 0;

    static void* ApplyOffset(const Type* targetType, const Type* sourceType, void* ptr);

    template<class TargetType, class SourceType>
    static TargetType DynamicCast(SourceType obj);

    const std::vector<const Type*>& GetBases() const;

    std::vector<const FieldInfo*> GetFields() const;

    const FieldInfo* GetField(std::string_view name) const;

    std::vector<const MethodInfo*> GetMethods() const;

    std::vector<const MethodInfo*> GetMethods(std::string_view name) const;

    const MethodInfo* GetMethod(std::string_view name, std::vector<const Type*> paramTypes) const;

    const ConstructorInfo* GetConstructor(std::vector<const Type*> paramTypes) const;

    std::vector<const ConstructorInfo*> GetConstructors() const;

    const DestructorInfo* GetDestructor() const;

    virtual bool IsNumber() const        = 0;
    virtual bool IsIntegral() const      = 0;
    virtual bool IsFloatingPoint() const = 0;

  private:
    hash32           _hash;
    std::type_index  _typeIndex;
    std::string_view _name;

    std::vector<const Type*> _bases;

    std::vector<FieldInfo*>       _fields;
    std::vector<MethodInfo*>      _methods;
    std::vector<ConstructorInfo*> _ctors;

    DestructorInfo* _dtor;
};

namespace Detail {

template<class T>
class TypeImpl : public Type {
  public:
    TypeImpl(std::string_view name) : Type(name, typeid(T)) {}
    void* Cast(void* ptr) const override { return static_cast<void*>(static_cast<T*>(ptr)); }

    bool IsNumber() const override { return IsIntegral() || IsFloatingPoint(); }
    bool IsIntegral() const override { return std::integral<T>; }
    bool IsFloatingPoint() const override { return std::floating_point<T>; }
};

} // namespace Detail

} // namespace EngineS

template<>
struct std::hash<EngineS::Type> {
    std::size_t operator()(const EngineS::Type& type) { return type.GetHashValue(); }
};

#include "Reflection/Impl/Type.inl"