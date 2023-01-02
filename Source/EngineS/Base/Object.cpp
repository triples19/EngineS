#include "Base/Object.hpp"
#include "Reflection/Type.hpp"

#include <memory>

namespace EngineS {

Type* Object::__es_type = new Detail::TypeImpl<EngineS::Object>("EngineS::Object", nullptr);

Object::Object()  = default;
Object::~Object() = default;

} // namespace EngineS