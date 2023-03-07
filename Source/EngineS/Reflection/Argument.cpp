#include "Reflection/Argument.hpp"
#include "Reflection/Variant.hpp"

namespace EngineS {

Argument::Argument() : _ptr(nullptr), _type(nullptr) {}

Argument::Argument(Argument&& other) noexcept : _ptr(other._ptr), _type(other._type) {}

Argument::Argument(const Argument& other) : _ptr(other._ptr), _type(other._type) {}

Argument::Argument(Variant& variant) : _ptr(variant.GetPointer()), _type(variant.GetType()) {}

Argument::Argument(const Variant& variant) : _ptr(variant.GetPointer()), _type(variant.GetType()) {}

const Type* Argument::GetType() const {
    return _type;
}

} // namespace EngineS