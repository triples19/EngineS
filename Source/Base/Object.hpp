#pragma once

#include <cstddef>

namespace EngineS {

class Object {
  public:
    static Object* Create();

    Object();
    virtual ~Object();

    std::size_t GetReferenceCount() const;

    void Retain();
    void Release();
    void AutoRelease();

  protected:
    std::size_t _referenceCount;
};

} // namespace EngineS