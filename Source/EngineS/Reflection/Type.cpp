#include "Reflection/Type.hpp"
#include "Base/Hash.hpp"
#include "Reflection/ConstructorInfo.hpp"
#include "Reflection/DestructorInfo.hpp"
#include "Reflection/FieldInfo.hpp"
#include "Reflection/MemberInfo.hpp"
#include "Reflection/MethodInfo.hpp"
#include "Reflection/TypeRegistry.hpp"

#include <algorithm>
#include <ranges>

namespace EngineS {

Type::~Type() {
    for (auto field : _fields) {
        delete field;
    }
    for (auto method : _methods) {
        delete method;
    }
    for (auto ctor : _ctors) {
        delete ctor;
    }
    delete _dtor;
}

Type::Type(std::string_view name, std::type_index typeIndex) :
    _name(name), _typeIndex(typeIndex), _hash(Hasher<std::string_view> {}(name)), _dtor(nullptr) {}

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
    return std::ranges::any_of(_bases, [type](const Type* base) {
        if (base == nullptr)
            return false;
        return base->DerivedFrom(type);
    });
}

const std::vector<const Type*>& Type::GetBases() const {
    return _bases;
}

std::vector<const FieldInfo*> Type::GetFields() const {
    std::vector<const FieldInfo*> ret;
    ret.reserve(_fields.size());
    for (auto field : _fields) {
        ret.push_back(field);
    }
    return ret;
}

const FieldInfo* Type::GetField(std::string_view name) const {
    auto iter = std::ranges::find_if(_fields, [&](const FieldInfo* info) { return info->GetName() == name; });
    if (iter == _fields.end())
        return nullptr;
    return *iter;
}

std::vector<const MethodInfo*> Type::GetMethods() const {
    std::vector<const MethodInfo*> ret;
    ret.reserve(_methods.size());
    for (auto method : _methods) {
        ret.push_back(method);
    }
    return ret;
}

std::vector<const MethodInfo*> Type::GetMethods(std::string_view name) const {
    std::vector<const MethodInfo*> ret;
    for (auto method : _methods) {
        if (method->GetName() == name)
            ret.push_back(method);
    }
    return ret;
}

const MethodInfo*
Type::GetMethod(std::string_view name, const Type* returnType, std::vector<const Type*> paramTypes) const {
    auto iter = std::ranges::find_if(_methods, [&](const MethodInfo* info) {
        return info->GetName() == name && info->GetReturnType() == returnType &&
               std::ranges::equal(paramTypes, info->GetParameterInfos(), {}, {}, [](const ParameterInfo& info) {
                   return info.GetType();
               });
    });
    if (iter == _methods.end())
        return nullptr;
    return *iter;
}

void* Type::ApplyOffset(const Type* targetType, const Type* sourceType, void* ptr) {
    if (targetType == sourceType || ptr == nullptr)
        return ptr;

    const auto& bases = sourceType->GetBases();
    auto        iter  = std::ranges::find(bases, targetType);
    if (iter == bases.end())
        return nullptr;
    return static_cast<void*>(targetType->Cast(sourceType->Cast(ptr)));
}

const ConstructorInfo* Type::GetConstructor(std::vector<const Type*> paramTypes) const {
    auto iter = std::ranges::find_if(_ctors, [&](const ConstructorInfo* info) {
        return std::ranges::equal(paramTypes, info->GetParameterInfos(), {}, {}, [](const ParameterInfo& paramInfo) {
            return paramInfo.GetType();
        });
    });
    if (iter == _ctors.end())
        return nullptr;
    return *iter;
}

std::vector<const ConstructorInfo*> Type::GetConstructors() const {
    std::vector<const ConstructorInfo*> ret;
    ret.reserve(_ctors.size());
    std::ranges::transform(_ctors, std::back_inserter(ret), [](auto x) { return x; });
    return ret;
}

const DestructorInfo* Type::GetDestructor() const {
    return _dtor;
}

} // namespace EngineS