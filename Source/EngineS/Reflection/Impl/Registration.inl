#pragma once

#include "Base/Hash.hpp"
#include "Reflection/ConstructorInfo.hpp"
#include "Reflection/DestructorInfo.hpp"
#include "Reflection/FieldInfo.hpp"
#include "Reflection/MethodInfo.hpp"
#include "Reflection/Type.hpp"
#include "Reflection/TypeRegistry.hpp"

namespace EngineS::Registration {

template<class T>
Class<T>::Class(std::string_view name) {
    _type = new Detail::TypeImpl<T>(name);
    TypeRegistry::Instance()->RegisterType(_type);
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
    std::vector<std::type_index> indices;
    indices.reserve(sizeof...(Ts));
    ((indices.emplace_back(typeid(Ts))), ...);
    TypeRegistry::Instance()->AddBases(_type, indices);
    return *this;
}

template<class T>
template<class Ptr>
Class<T>& Class<T>::Field(std::string_view name, Ptr ptr, AccessLevel accessLevel) {
    auto info = new Detail::FieldInfoImpl(name, ptr, accessLevel);
    _type->_fields.push_back(info);
    return *this;
}

template<class T>
template<class Ptr>
Class<T>&
Class<T>::Method(std::string_view name, Ptr ptr, const std::vector<std::string_view>& params, AccessLevel accessLevel) {
    auto info = new Detail::MethodInfoImpl(name, ptr, params, accessLevel);
    _type->_methods.push_back(info);
    return *this;
}

template<class T>
template<class... Params>
Class<T>& Class<T>::Constructor(const std::vector<std::string_view>& params, AccessLevel accessLevel) {
    if constexpr (std::constructible_from<T, Params...>) {
        auto ctor = new Detail::ConstructorInfoImpl<T, Params...>(params, accessLevel);
        _type->_ctors.push_back(ctor);
        if (_type->_dtor == nullptr) {
            _type->_dtor = new Detail::DestructorInfoImpl<T>();
        }
    }
    return *this;
}

} // namespace EngineS::Registration