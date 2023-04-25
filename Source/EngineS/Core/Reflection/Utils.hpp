#pragma once

#include "Core/Concepts.hpp"
#include "Core/Platform.hpp"
#include "Core/TypeTraits.hpp"

#include <algorithm>
#include <iterator>
#include <memory>

namespace EngineS {

class Type;

template<class T>
concept IsRawVoidPointer = SameAs<void*, AddPointer<RawType<T>>>;

template<class T>
concept IsVoidPointer = IsPointer<T> && IsRawVoidPointer<T> && PointerCount<T>() == 1;

template<class T>
concept HasGetTypeMethod = //
    requires(const T* ptr) {
        { ptr->GetType() } -> SameAs<const Type*>;
    };

template<class T>
inline auto RawAddressOf(T& data) {
    if constexpr (IsPointer<T> && PointerCount<T>() >= 1 && !IsVoidPointer<T>) {
        return RawAddressOf<RemovePointer<T>>(*data);
    } else if constexpr (IsVoidPointer<T>) {
        return data;
    } else {
        return std::addressof(data);
    }
}

namespace Detail {
template<class, bool, bool, class, class...>
struct MethodTypeImpl;

template<class Parent, class Ret, class... Params>
struct MethodTypeImpl<Parent, false, true, Ret, Params...> {
    using Type = Ret (Parent::*)(Params...) const;
};

template<class Parent, class Ret, class... Params>
struct MethodTypeImpl<Parent, false, false, Ret, Params...> {
    using Type = Ret (Parent::*)(Params...);
};

template<bool IsConst, class Parent, class Ret, class... Params>
struct MethodTypeImpl<Parent, true, IsConst, Ret, Params...> {
    using Type = Ret (*)(Params...);
};
} // namespace Detail

template<class Parent, bool IsStatic, bool IsConst, class Ret, class... Params>
using MethodType = typename Detail::MethodTypeImpl<Parent, IsStatic, IsConst, Ret, Params...>::Type;

template<class SourceContainer, class TargetContainer>
    requires IsConvertible<typename SourceContainer::value_type, typename TargetContainer::value_type>
inline TargetContainer* CopyContainer(const void* ptr) {
    using SourceValueType = typename SourceContainer::value_type;
    using TargetValueType = typename TargetContainer::value_type;

    auto source = static_cast<const SourceContainer*>(ptr);
    auto target = new TargetContainer;
    std::ranges::transform(*source, std::inserter(*target, target->end()), [&](const SourceValueType& val) {
        return TargetValueType(val);
    });
    return target;
}

} // namespace EngineS

#include "TypeOf.hpp"

#define ES_REFL_ENABLE                        \
  public:                                     \
    ES_BEGIN_DISABLE_OVERRIDE_WARNING         \
    virtual const Type* GetType() const {     \
        return TypeOf(*this);                 \
    }                                         \
    virtual void* GetPointer() {              \
        return reinterpret_cast<void*>(this); \
    }                                         \
    ES_END_DISABLE_OVERRIDE_WARNING           \
  private:
