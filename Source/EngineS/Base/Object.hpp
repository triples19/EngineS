#pragma once

#include "Base/Ref.hpp"

namespace EngineS {

#define ES_OBJECT ES_REFL_ENABLE

class Type;

class Object : public Ref {
    ES_OBJECT
  public:
    Object();
    virtual ~Object();
};

} // namespace EngineS