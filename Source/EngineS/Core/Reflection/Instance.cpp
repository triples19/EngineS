#include "Instance.hpp"
#include "Variant.hpp"

namespace EngineS {

Instance::Instance() : _type(nullptr), _address(nullptr) {}

Instance::Instance(const Variant& var) : _type(var.GetType()), _address(var.GetRawAddress()) {}

Instance::Instance(const Instance& other) : _type(other._type), _address(other._address) {}

bool Instance::IsValid() const {
    return _address != nullptr;
}

} // namespace EngineS