#pragma once

#include "Base/PrimitiveTypes.hpp"
#include "Reflection/Utils.hpp"

#include <cstddef>

namespace EngineS {

class Ref {
    ES_REFL_ENABLE
  public:
    Ref();
    virtual ~Ref();

    Ref(const Ref&)            = delete;
    Ref& operator=(const Ref&) = delete;

    void Retain();
    void Release();

    i32 GetRefCount() const;

  private:
    void AutoRelease();

  protected:
    i32 _refCount;
};

} // namespace EngineS