#include "Base/AutoReleasePool.hpp"
#include "Base/PoolManager.hpp"
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

} // namespace EngineS