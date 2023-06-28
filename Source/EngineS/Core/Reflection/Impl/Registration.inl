#pragma once

#include "Core/Concepts.hpp"
#include "Core/Hash.hpp"
#include "Core/Reflection/Constructor.hpp"
#include "Core/Reflection/Destructor.hpp"
#include "Core/Reflection/Field.hpp"
#include "Core/Reflection/Method.hpp"
#include "Core/Reflection/Type.hpp"
#include "Core/Reflection/TypeRegistry.hpp"

namespace EngineS::Registration {

template<class T>
Class<T>::Class(std::string_view name) {
    _type = TypeRegistry::Instance()->GetOrCreateType<T>();
    _type->SetName(name);
}

template<class T>
Class<T>::~Class() {
    if constexpr (std::default_initializable<T>) {
        if (_type->GetConstructor({}) == nullptr) {
            Constructor<>({}); // Add a default constructor
        }
    }
}

template<class T>
template<class... Ts>
Class<T>& Class<T>::Bases() {
    (_type->_bases.push_back(TypeRegistry::Instance()->GetOrCreateType<Ts>()), ...);
    return *this;
}

template<class T>
template<class Ptr>
Class<T>& Class<T>::Field(std::string_view name, Ptr ptr, AccessLevel accessLevel) {
    auto info = new Detail::FieldImpl(name, ptr, accessLevel);
    _type->_fields.push_back(info);
    return *this;
}

template<class T>
template<class Ptr>
Class<T>&
Class<T>::Method(std::string_view name, Ptr ptr, const std::vector<std::string_view>& params, AccessLevel accessLevel) {
    auto info = new Detail::MethodImpl(name, ptr, params, accessLevel);
    _type->_methods.push_back(info);
    return *this;
}

template<class T>
template<class... Params>
Class<T>& Class<T>::Constructor(const std::vector<std::string_view>& params, AccessLevel accessLevel) {
    if constexpr (std::constructible_from<T, Params...>) {
        auto ctor = new Detail::ConstructorImpl<T, Params...>(params, accessLevel);
        _type->_ctors.push_back(ctor);
        if (_type->_dtor == nullptr) {
            _type->_dtor = new Detail::DestructorImpl<T>();
        }
    }
    return *this;
}

template<class T>
    requires std::is_enum_v<T>
Enum<T>::Enum(std::string_view name) {
    _info = new Detail::EnumImpl<T>(name);
    TypeRegistry::Instance()->RegisterEnum(_info);
}

template<class T>
    requires std::is_enum_v<T>
Enum<T>& Enum<T>::Value(std::string_view name, T val) {
    _info->_map[name] = static_cast<std::underlying_type_t<T>>(val);
    return *this;
}

} // namespace EngineS::Registration
