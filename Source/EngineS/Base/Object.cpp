#include "Base/Object.hpp"
#include "Reflection/Registration.hpp"
#include "Reflection/Type.hpp"

#include <memory>

namespace EngineS {

const Type* Object::__es_type = Registration::Class<EngineS::Object>("EngineS::Object", nullptr).Get();

Object::Object()  = default;
Object::~Object() = default;

} // namespace EngineS