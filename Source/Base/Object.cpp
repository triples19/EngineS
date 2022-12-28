#include "Base/Object.hpp"
#include "Base/Type.hpp"

#include <memory>

namespace EngineS {

static Detail::TypeImpl<Object> s_Object_Type("Object", nullptr);
const Type*                     Object::GetType() {
    return &s_Object_Type;
}

Object* Object::Create() {
    auto obj = new (std::nothrow) Object();
    if (obj) {
        obj->AutoRelease();
    }
    return obj;
}

Object::Object() {}

Object::~Object() {}

} // namespace EngineS