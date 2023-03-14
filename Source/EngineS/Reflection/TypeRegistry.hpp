#pragma once

#include "Base/PrimitiveTypes.hpp"

#include <string>
#include <typeindex>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace EngineS {

class Type;

class TypeRegistry {
  public:
    static TypeRegistry* Instance();

    void RegisterType(Type* type);

    const Type* GetType(std::string_view name) const;
    const Type* GetType(hash32 hash) const;
    const Type* GetType(std::type_index typeIndex) const;

    std::vector<const Type*> GetTypes() const;

    void AddBases(const Type* type, const std::vector<std::type_index>& baseIndices);

    void ProcessBases();

  private:
    void GetBasesOfType(Type* type);

  private:
    std::unordered_map<hash32, Type*>                _types;
    std::unordered_map<std::type_index, const Type*> _indexToType;

    std::unordered_set<const Type*>                          _processedTypes;
    std::unordered_map<hash32, std::vector<std::type_index>> _tempBases;
};

} // namespace EngineS