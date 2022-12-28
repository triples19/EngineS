#pragma once

#include "Base/Object.hpp"
#include "Base/Type.hpp"

#include <concepts>

namespace EngineS {

template<class T, class U>
concept SameAs = std::same_as<T, U>;

template<class Derived, class Base>
concept DerivedFrom = std::derived_from<Derived, Base>;

} // namespace EngineS