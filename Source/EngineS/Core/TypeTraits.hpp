#pragma once

#include <type_traits>

#include "Core/Concepts.hpp"

namespace EngineS {

template<class T>
using RemoveCV = std::remove_cv_t<T>;

template<class T>
using RemoveCVRef = std::remove_cvref_t<T>;

template<class T>
using RemoveReference = std::remove_reference_t<T>;

template<class T>
using AddPointer = std::add_pointer_t<T>;

template<class T>
using RemovePointer = std::remove_pointer_t<T>;

namespace Detail {
template<class T>
struct RemovePointersImpl {
    using Type = T;
};

template<IsPointer T>
struct RemovePointersImpl<T> {
    using Type = typename RemovePointersImpl<RemovePointer<T>>::Type;
};
} // namespace Detail
template<class T>
using RemovePointers = typename Detail::RemovePointersImpl<T>::Type;

template<class T>
inline constexpr std::size_t PointerCount() {
    if constexpr (IsPointer<T>) {
        return PointerCount<RemovePointer<T>>() + 1;
    } else {
        return 0;
    }
}

namespace Detail {
template<class T>
struct RawTypeImpl {
    using Type = RemoveCVRef<T>;
};
template<IsPointer T>
struct RawTypeImpl<T> {
    using Type = typename RawTypeImpl<RemovePointer<T>>::Type;
};
} // namespace Detail

template<class T>
using RawType = typename Detail::RawTypeImpl<T>::Type;

} // namespace EngineS