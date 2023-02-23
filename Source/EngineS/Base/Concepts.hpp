#pragma once

#include <concepts>

namespace EngineS {

template<class T, class U>
concept SameAs = std::same_as<T, U>;

template<class Derived, class Base>
concept DerivedFrom = std::derived_from<Derived, Base>;

template<class T>
concept DefaultInitializable = std::default_initializable<T>;

template<class T>
concept IsPointer = std::is_pointer_v<T>;

namespace Detail {
template<typename>
struct IsConstCallableMethodImpl;

template<typename ParentType, typename ReturnType, typename... ArgType>
struct IsConstCallableMethodImpl<ReturnType (ParentType::*)(ArgType...)> {
    static constexpr bool Value = false;
};

template<typename ParentType, typename ReturnType, typename... ArgType>
struct IsConstCallableMethodImpl<ReturnType (ParentType::*)(ArgType...) const> {
    static constexpr bool Value = true;
};
} // namespace Detail

template<class T>
concept ConstCallableMethod = Detail::IsConstCallableMethodImpl<T>::Value;

template<class From, class To>
concept ExplicitlyConvertibleTo = requires(const From& from) { static_cast<To>(from); };

class Object;

template<class T>
concept IsObject = DerivedFrom<T, Object>;

template<class T>
concept IsObjectPointer = IsPointer<T> && DerivedFrom<std::remove_pointer_t<T>, Object>;

} // namespace EngineS