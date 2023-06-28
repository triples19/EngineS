#pragma once

#include "Core/PrimitiveTypes.hpp"

#include <string>
#include <string_view>
#include <typeindex>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace EngineS {

class Type;
class EnumInfo;

class TypeRegistry {
  public:
    static TypeRegistry* Instance();

    void RegisterType(Type* type);

    template<class T>
    Type* GetOrCreateType();

    const Type* GetType(std::string_view name) const;
    const Type* GetType(hash32 hash) const;
    const Type* GetType(std::type_index typeIndex) const;

    std::vector<const Type*> GetTypes() const;

    void RegisterEnum(EnumInfo* enumInfo);

    const EnumInfo* GetEnum(std::string_view name) const;

  private:
    std::unordered_map<hash32, Type*>          _types;
    std::unordered_map<std::type_index, Type*> _indexToType;

    std::unordered_map<hash32, EnumInfo*> _enums;
};

} // namespace EngineS

#include "Core/Hash.hpp"
#include "Core/Reflection/Type.hpp"

namespace EngineS {

template<class T>
Type* TypeRegistry::GetOrCreateType() {
    auto iter = _indexToType.find(typeid(T));
    if (iter != _indexToType.end()) {
        return iter->second;
    }
    auto type = new Detail::TypeImpl<T>("");
    RegisterType(type);
    return type;
}

} // namespace EngineS