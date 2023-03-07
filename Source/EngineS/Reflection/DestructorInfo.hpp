#pragma once

namespace EngineS {

class Instance;

class DestructorInfo {
  public:
    virtual ~DestructorInfo() = default;

    virtual void Invoke(Instance instance) const = 0;
};

} // namespace EngineS

#include "Reflection/Impl/DestructorInfo.inl"