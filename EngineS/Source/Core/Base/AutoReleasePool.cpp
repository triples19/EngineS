#include "Core/Base/AutoReleasePool.hpp"
#include "Core/Base/PoolManager.hpp"

namespace EngineS {

AutoReleasePool::AutoReleasePool() {
	_managedObjects.reserve(150);
	PoolManager::Instance()->PushPool(this);
}

AutoReleasePool::~AutoReleasePool() {
	Clear();
	PoolManager::Instance()->PopPool();
}

void AutoReleasePool::AddObject(Object* obj) {
	_managedObjects.push_back(obj);
}

void AutoReleasePool::Clear() {
	std::vector<Object*> releasings;
	releasings.swap(_managedObjects);
	for (const auto& obj : releasings) {
		obj->Release();
	}
}

} // namespace EngineS