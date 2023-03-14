#include "Reflection/TypeRegistry.hpp"
#include "Base/Hash.hpp"
#include "Reflection/Registration.hpp"
#include "Reflection/Type.hpp"

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

void TypeRegistry::AddBases(const Type* type, const std::vector<std::type_index>& baseIndices) {
    auto& storedBases = _tempBases[type->GetHashValue()];
    storedBases.insert(storedBases.end(), baseIndices.begin(), baseIndices.end());
}

void TypeRegistry::GetBasesOfType(Type* type) {
    if (_processedTypes.contains(type))
        return;

    for (const auto& baseIndex : _tempBases[type->GetHashValue()]) {
        auto base = const_cast<Type*>(GetType(baseIndex));
        assert(base);
        GetBasesOfType(base);
        type->_bases.push_back(base);
        std::ranges::copy(base->_bases, std::back_inserter(type->_bases));
        std::ranges::copy(base->_methods, std::back_inserter(type->_methods));
        std::ranges::copy(base->_fields, std::back_inserter(type->_fields));
    }
    _processedTypes.insert(type);
}

void TypeRegistry::ProcessBases() {
    for (const auto& [idx, baseIndex] : _tempBases) {
        auto type = const_cast<Type*>(GetType(idx));
        GetBasesOfType(type);
    }
    _tempBases.clear();
}

} // namespace EngineS