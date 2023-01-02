#pragma once

#include "Base/PrimitiveTypes.hpp"

#include <cstddef>

namespace EngineS {

class Ref {
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