#pragma once

#include "Base/Ref.hpp"

namespace EngineS {

class Type;

#define ES_OBJECT                            \
  public:                                    \
    static const Type* GetTypeStatic() {     \
        return __es_type;                    \
    }                                        \
    virtual const Type* GetType() override { \
        return GetTypeStatic();              \
    }                                        \
                                             \
  private:                                   \
    static const Type* __es_type;

class Object : public Ref {
  public:
    Object();
    virtual ~Object();

    static const Type*  GetTypeStatic() { return __es_type; }
    virtual const Type* GetType() { return GetTypeStatic(); }

  private:
    static const Type* __es_type;
};

} // namespace EngineS