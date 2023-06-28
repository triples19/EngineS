#include "TypeRegistry.hpp"
#include "Core/Hash.hpp"
#include "Registration.hpp"
#include "Type.hpp"

#include <cassert>
#include <memory>
#include <typeindex>

namespace EngineS {

static TypeRegistry* s_SharedInstance;

TypeRegistry* TypeRegistry::Instance() {
    if (!s_SharedInstance) {
        s_SharedInstance = new (std::nothrow) TypeRegistry;
        assert(s_SharedInstance != nullptr);
        Registration::DoRegistration();
    }
    return s_SharedInstance;
}

void TypeRegistry::RegisterType(Type* type) {
    _types[type->GetHashValue()]       = type;
    _indexToType[type->GetTypeIndex()] = type;
}

const Type* TypeRegistry::GetType(std::string_view name) const {
    auto hash = Hasher<std::string_view> {}(name);
    return GetType(hash);
}

const Type* TypeRegistry::GetType(hash32 hash) const {
    auto iter = _types.find(hash);
    if (iter != _types.end()) {
        return iter->second;
    }
    return nullptr;
}

const Type* TypeRegistry::GetType(std::type_index typeIndex) const {
    auto iter = _indexToType.find(typeIndex);
    if (iter != _indexToType.end()) {
        return iter->second;
    }
    return nullptr;
}

std::vector<const Type*> TypeRegistry::GetTypes() const {
    std::vector<const Type*> ret;
    ret.reserve(_types.size());
    std::ranges::transform(_types, std::back_inserter(ret), [](const auto& pair) { return pair.second; });
    return ret;
}

void TypeRegistry::RegisterEnum(EnumInfo* enumInfo) {
    auto hasher                         = Hasher<std::string_view> {};
    _enums[hasher(enumInfo->GetName())] = enumInfo;
}

const EnumInfo* TypeRegistry::GetEnum(std::string_view name) const {
    auto hash = Hasher<std::string_view> {}(name);
    auto iter = _enums.find(hash);
    if (iter == _enums.end()) {
        return nullptr;
    }
    return iter->second;
}

} // namespace EngineS