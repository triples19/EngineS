#pragma once

#include "Reflection/TypeOf.hpp"

namespace EngineS {

template<class T>
Argument::Argument(T& val) : _ptr(RawAddressOf(val)), _type(TypeOf<T>()) {}

template<class T>
Argument::Argument(const T& val) : _ptr(RawAddressOf(val)), _type(TypeOf<T>()) {}

template<class T>
decltype(auto) Argument::GetValue() const {
    if constexpr (std::is_pointer_v<T>) {
        return static_cast<T>(const_cast<void*>(_ptr));
    } else {
        using RawT = RemoveReference<T>;
        if constexpr (std::is_rvalue_reference_v<T>) {
            return std::move(*static_cast<RawT*>(const_cast<void*>(_ptr)));
        } else {
            return *static_cast<RawT*>(const_cast<void*>(_ptr));
        }
    }
}

} // namespace EngineS
