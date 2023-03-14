#pragma once

namespace EngineS {

class Type;

template<class>
inline const Type* TypeOf();

template<class T>
inline const Type* TypeOf(const T& val);

} // namespace EngineS

#include "Base/TypeTraits.hpp"
#include "Reflection/TypeRegistry.hpp"
#include "Reflection/Utils.hpp"

#include <typeinfo>

namespace EngineS {

template<class T>
concept CanGetTypeId = requires { typeid(RawType<T>); };

template<class T>
inline const Type* TypeOf() {
    if constexpr (CanGetTypeId<T>) {
        return TypeRegistry::Instance()->GetType(typeid(RawType<T>));
    }
    return nullptr;
}

template<class T>
inline const Type* TypeOf(const T& val) {
    if constexpr (HasGetTypeMethod<RawType<T>>) {
        if constexpr (IsPointer<T>) {
            return val->GetType();
        } else if constexpr (IsReference<T>) {
            return val.GetType();
        } else {
            return TypeOf<T>();
        }
    } else {
        return TypeOf<RawType<T>>();
    }
}

} // namespace EngineS