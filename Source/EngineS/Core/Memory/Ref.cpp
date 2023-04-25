#include "Ref.hpp"
#include "Core/Memory/AutoReleasePool.hpp"

namespace EngineS {

Ref::Ref() : _refCount(1) {
    AutoRelease();
}

Ref::~Ref() = default;

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
