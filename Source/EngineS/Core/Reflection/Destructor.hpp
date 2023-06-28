#pragma once

namespace EngineS {

class Instance;

class Destructor {
  public:
    virtual ~Destructor() = default;

    virtual void Invoke(Instance instance) const = 0;
};

} // namespace EngineS

#include "Core/Reflection/Impl/Destructor.inl"