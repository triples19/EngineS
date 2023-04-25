#pragma once

#include "Core/Reflection/TypeOf.hpp"
#include "Core/Reflection/Variant.hpp"

namespace EngineS::Registration {
template<class T>
    requires std::is_enum_v<T>
class Enum;
}

namespace EngineS::Detail {

template<class T>
class EnumInfoImpl : public EnumInfo {
    friend class ::EngineS::Registration::Enum<T>;

  public:
    EnumInfoImpl(std::string_view name) : _name(name) {}
    std::string_view GetName() const override { return _name; }
    const Type*      GetUnderlyingType() const override { return TypeOf<std::underlying_type_t<T>>(); }

    Variant GetValue(std::string_view name) const override {
        auto iter = _map.find(name);
        if (iter == _map.end()) {
            return {};
        } else {
            return iter->second;
        }
    }

    const EnumMap& GetValues() const override { return _map; }

  private:
    std::string_view _name;
    EnumMap          _map;
};

} // namespace EngineS::Detail