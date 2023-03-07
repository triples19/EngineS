#pragma once

#include "Reflection/TypeOf.hpp"

namespace EngineS {

template<class T>
Argument::Argument(T& val) : _ptr(std::addressof(val)), _type(TypeOf<T>()) {}

template<class T>
Argument::Argument(const T& val) : _ptr(std::addressof(val)), _type(TypeOf<T>()) {}

template<class T>
decltype(auto) Argument::GetValue() const {
    using RawType = RemoveReference<T>;
    if constexpr (std::is_rvalue_reference_v<T>) {
        return std::move(*reinterpret_cast<RawType*>(const_cast<void*>(_ptr)));
    } else {
        return *reinterpret_cast<RawType*>(const_cast<void*>(_ptr));
    }
}

} // namespace EngineS