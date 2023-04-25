#pragma once

#include "TypeOf.hpp"

#include <string>
#include <unordered_map>

namespace EngineS {

class Type;
class Variant;

using EnumMap = std::unordered_map<std::string_view, Variant>;

class EnumInfo {
  public:
    virtual std::string_view GetName() const                       = 0;
    virtual const Type*      GetUnderlyingType() const             = 0;
    virtual Variant          GetValue(std::string_view name) const = 0;
    virtual const EnumMap&   GetValues() const                     = 0;
};

} // namespace EngineS

#include "Core/Reflection/Impl/EnumInfo.inl"