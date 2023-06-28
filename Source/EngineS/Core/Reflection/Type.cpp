#include "Type.hpp"
#include "Constructor.hpp"
#include "Core/Hash.hpp"
#include "Destructor.hpp"
#include "Field.hpp"
#include "MemberInfo.hpp"
#include "Method.hpp"
#include "TypeRegistry.hpp"

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
    return std::ranges::any_of(GetBases(), [type](const Type* base) {
        if (base == nullptr)
            return false;
        return base->DerivedFrom(type);
    });
}

std::vector<const Type*> Type::GetBases() const {
    std::vector<const Type*> ret;
    for (auto base : _bases) {
        ret.push_back(base);
        auto b = base->GetBases();
        ret.insert(ret.end(), b.begin(), b.end());
    }
    return ret;
}

std::vector<const Field*> Type::GetFields() const {
    std::vector<const Field*> ret;
    ret.reserve(_fields.size());
    for (auto field : _fields) {
        ret.push_back(field);
    }
    return ret;
}

const Field* Type::GetField(std::string_view name) const {
    auto iter = std::ranges::find_if(_fields, [&](const Field* info) { return info->GetName() == name; });
    if (iter == _fields.end())
        return nullptr;
    return *iter;
}

std::vector<const Method*> Type::GetMethods() const {
    std::vector<const Method*> ret;
    ret.reserve(_methods.size());
    for (auto method : _methods) {
        ret.push_back(method);
    }
    return ret;
}

std::vector<const Method*> Type::GetMethods(std::string_view name) const {
    std::vector<const Method*> ret;
    for (auto method : _methods) {
        if (method->GetName() == name)
            ret.push_back(method);
    }
    return ret;
}

const Method* Type::GetMethod(std::string_view name, std::vector<const Type*> paramTypes) const {
    auto iter = std::ranges::find_if(_methods, [&](const Method* info) {
        return info->GetName() == name &&
               std::ranges::equal(paramTypes, info->GetParameterInfos(), {}, {}, [](const Parameter& info) {
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

const Constructor* Type::GetConstructor(std::vector<const Type*> paramTypes) const {
    auto iter = std::ranges::find_if(_ctors, [&](const Constructor* info) {
        return std::ranges::equal(paramTypes, info->GetParameterInfos(), {}, {}, [](const Parameter& paramInfo) {
            return paramInfo.GetType();
        });
    });
    if (iter == _ctors.end())
        return nullptr;
    return *iter;
}

std::vector<const Constructor*> Type::GetConstructors() const {
    std::vector<const Constructor*> ret;
    ret.reserve(_ctors.size());
    std::ranges::transform(_ctors, std::back_inserter(ret), [](auto x) { return x; });
    return ret;
}

const Destructor* Type::GetDestructor() const {
    return _dtor;
}

void Type::SetName(std::string_view name) {
    _name = name;
    _hash = Hasher<std::string_view> {}(name);
}

} // namespace EngineS