#pragma once

#include <concepts>

namespace EngineS {

template<class T, class U>
concept SameAs = std::same_as<T, U>;

template<class T, class U>
concept NotSameAs = not std::same_as<T, U>;

template<class T, class U>
concept DifferentAs = std::same_as<T, U>;

template<class Derived, class Base>
concept DerivedFrom = std::derived_from<Derived, Base>;

template<class T>
concept DefaultInitializable = std::default_initializable<T>;

template<class T>
concept IsPointer = std::is_pointer_v<T>;

template<class T>
concept IsObject = std::is_object_v<T>;

template<class T>
concept IsReference = std::is_reference_v<T>;

template<class From, class To>
concept ExplicitlyConvertibleTo = requires(const From& from) { static_cast<To>(from); };

template<class From, class To>
concept IsConvertible = std::is_convertible_v<From, To>;

} // namespace EngineS
