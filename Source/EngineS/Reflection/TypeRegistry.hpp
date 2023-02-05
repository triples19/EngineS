#pragma once

#include "Base/PrimitiveTypes.hpp"

#include <string>
#include <unordered_map>

namespace EngineS {

class Type;

class TypeRegistry {
  public:
    static TypeRegistry* Instance();

    void RegisterType(const Type* type);

    const Type* GetType(std::string_view name) const;
    const Type* GetType(hash32 hash) const;

  private:
    std::unordered_map<hash32, const Type*> _types;
};

} // namespace EngineS