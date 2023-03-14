#pragma once

#include "Base/Concepts.hpp"
#include "Base/TypeTraits.hpp"

namespace EngineS {

class Type;
class Variant;

class Instance {
  public:
    Instance();

    Instance(const Variant& var);

    template<class T>
        requires NotSameAs<RemoveCVRef<T>, Instance> && NotSameAs<RemoveCVRef<T>, Variant>
    Instance(T& val);

    Instance(const Instance& other);

    bool IsValid() const;

    template<class T>
    inline T* TryConvert() const;

  private:
    const Type* _type;
    void*       _address;
};

} // namespace EngineS

#include "Reflection/Type.hpp"
#include "Reflection/TypeOf.hpp"
#include "Reflection/Utils.hpp"

namespace EngineS {

template<class T>
    requires NotSameAs<RemoveCVRef<T>, Instance> && NotSameAs<RemoveCVRef<T>, Variant>
Instance::Instance(T& val) : _type(TypeOf(val)), _address(RawAddressOf(val)) {}

template<class T>
T* Instance::TryConvert() const {
    if (!IsValid())
        return nullptr;
    return static_cast<T*>(Type::ApplyOffset(TypeOf<T>(), _type, _address));
}

} // namespace EngineS