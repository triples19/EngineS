#include "Reflection/TypeRegistry.hpp"
#include "Base/Hash.hpp"
#include "Reflection/Registration.hpp"
#include "Reflection/Type.hpp"

#include <cassert>
#include <memory>

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

void TypeRegistry::RegisterType(const Type* type) {
    _types[type->GetHashValue()] = type;
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

} // namespace EngineS