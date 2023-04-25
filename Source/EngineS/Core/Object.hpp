#pragma once

#include "Core/Memory/Ref.hpp"

namespace EngineS {

#define ES_OBJECT ES_REFL_ENABLE

class Type;

class Object : public Ref {
    ES_OBJECT
  public:
    Object()          = default;
    virtual ~Object() = default;
};

} // namespace EngineS