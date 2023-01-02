#pragma once

#include <concepts>

namespace EngineS {

template<class T, class U>
concept SameAs = std::same_as<T, U>;

template<class Derived, class Base>
concept DerivedFrom = std::derived_from<Derived, Base>;

template<class T>
concept DefaultInitializable = std::default_initializable<T>;

} // namespace EngineS