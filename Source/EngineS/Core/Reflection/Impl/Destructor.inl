#pragma once

#include "Core/Reflection/Instance.hpp"

namespace EngineS::Detail {

template<class T>
class DestructorImpl : public Destructor {
  public:
    void Invoke(Instance instance) const override {
        delete instance.TryConvert<T>();
    }
};

} // namespace EngineS::Detail