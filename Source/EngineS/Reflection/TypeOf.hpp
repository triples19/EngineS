#pragma once

namespace EngineS {

class Type;

template<class>
inline const Type* TypeOf();

template<class T>
inline const Type* TypeOf(const T& val);

} // namespace EngineS

#include "Base/Concepts.hpp"
#include "Base/Object.hpp"
#include "Base/Variant.hpp"
#include "Reflection/TypeRegistry.hpp"

namespace EngineS {

template<class T>
inline const Type* TypeOf() {
    return nullptr;
}

template<class T>
    requires IsObject<T> || IsObjectPointer<T>
inline const Type* TypeOf() {
    return std::remove_pointer_t<T>::GetTypeStatic();
}

template<class T>
inline const Type* TypeOf(const T& val) {
    if constexpr (IsObjectPointer<T>) {
        return val->GetType();
    } else if constexpr (SameAs<T, Variant>) {
        return val.GetType();
    } else {
        return TypeOf<T>();
    }
}

#define ES_DEFINE_TYPEOF(type)                           \
    template<>                                           \
    inline const Type* TypeOf<type>() {                  \
        return TypeRegistry::Instance()->GetType(#type); \
    }

ES_DEFINE_TYPEOF(void)
ES_DEFINE_TYPEOF(int)
ES_DEFINE_TYPEOF(bool)
ES_DEFINE_TYPEOF(float)
ES_DEFINE_TYPEOF(double)

} // namespace EngineS