#pragma once

#include "Reflection/Instance.hpp"

namespace EngineS::Detail {

template<class T>
class DestructorInfoImpl : public DestructorInfo {
  public:
    void Invoke(Instance instance) const override { delete instance.TryConvert<T>(); }
};

} // namespace EngineS::Detail