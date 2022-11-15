#include "Core/Base/PoolManager.hpp"
#include "Core/Base/AutoReleasePool.hpp"
#include "Core/Base/Macros.hpp"

namespace EngineS {

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