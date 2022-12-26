#pragma once

#include "Base/Ref.hpp"

namespace EngineS {

class Object : public Ref {
  public:
    static Object* Create();

    Object();
    virtual ~Object();
};

} // namespace EngineS