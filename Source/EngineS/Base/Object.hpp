#pragma once

#include "Base/Ref.hpp"

namespace EngineS {

class Type;

#define ES_OBJECT                 \
  public:                         \
    static const Type* GetType(); \
                                  \
  private:                        \
    static Type* __es_type;

class Object : public Ref {
  public:
    static Object* Create();

    Object();
    virtual ~Object();

    static const Type* GetType();
};

} // namespace EngineS