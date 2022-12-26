#include "Object.hpp"

#include <memory>

namespace EngineS {

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