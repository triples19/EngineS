#include "Base/AutoReleasePool.hpp"
#include "Base/Macros.hpp"
#include "Base/Ref.hpp"

namespace EngineS {

AutoReleasePool::AutoReleasePool() {
    _managedObjects.reserve(150);
    PoolManager::Instance()->PushPool(this);
}

AutoReleasePool::~AutoReleasePool() {
    Clear();
    PoolManager::Instance()->PopPool();
}

void AutoReleasePool::AddObject(Ref* obj) {
    _managedObjects.push_back(obj);
}

void AutoReleasePool::Clear() {
    std::vector<Ref*> releasings;
    releasings.swap(_managedObjects);
    for (const auto& obj : releasings) {
        obj->Release();
    }
}

static PoolManager* s_SharedInstance;

PoolManager* PoolManager::Instance() {
    if (!s_SharedInstance) {
        s_SharedInstance = new (std::nothrow) PoolManager;
        ES_ASSERT_NOMSG(s_SharedInstance != nullptr);
        // Add first pool
        new AutoReleasePool();
    }
    return s_SharedInstance;
}

AutoReleasePool* PoolManager::GetCurrentPool() const {
    return _releasePools.back();
}

PoolManager::PoolManager() {
    _releasePools.reserve(10);
}

PoolManager::~PoolManager() {
    while (!_releasePools.empty()) {
        auto pool = _releasePools.back();
        delete pool;
    }
}

void PoolManager::PushPool(AutoReleasePool* pool) {
    _releasePools.push_back(pool);
}

void PoolManager::PopPool() {
    assert(!_releasePools.empty());
    _releasePools.pop_back();
}

} // namespace EngineS