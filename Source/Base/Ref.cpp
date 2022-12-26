#include "Base/Ref.hpp"
#include "Base/AutoReleasePool.hpp"
#include "Base/PoolManager.hpp"

namespace EngineS {

Ref::Ref() : _refCount(1) {}

Ref::~Ref() {}

void Ref::Retain() {
    ++_refCount;
}

void Ref::Release() {
    --_refCount;
    if (_refCount == 0) {
        delete this;
    }
}

void Ref::AutoRelease() {
    PoolManager::Instance()->GetCurrentPool()->AddObject(this);
}

i32 Ref::GetRefCount() const {
    return _refCount;
}

} // namespace EngineS
