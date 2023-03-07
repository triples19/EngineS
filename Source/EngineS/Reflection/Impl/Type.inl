#pragma once

#include "Reflection/TypeOf.hpp"

namespace EngineS {

template<class T>
bool Type::Is() const {
    return Is(TypeOf<T>());
}

template<class T>
bool Type::IsBaseOf() const {
    return IsBaseOf(TypeOf<T>());
}

template<class T>
bool Type::DerivedFrom() const {
    return DerivedFrom(TypeOf<T>());
}

template<class TargetType, class SourceType>
TargetType Type::DynamicCast(SourceType obj) {
    using SourceTypeNoCVPtr = RemoveCV<RemovePointers<SourceType>>;
    return static_cast<TargetType>(Type::ApplyOffset(
        TypeOf<TargetType>(),
        static_cast<SourceTypeNoCVPtr*>(obj)->GetType(),
        static_cast<SourceTypeNoCVPtr*>(obj)->GetRawPointer()
    ));
}

} // namespace EngineS