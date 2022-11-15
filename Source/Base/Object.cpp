#include "Object.hpp"
#include "AutoReleasePool.hpp"
#include "PoolManager.hpp"

#include <memory>

namespace EngineS {

Object* Object::Create() {
	auto obj = new (std::nothrow) Object();
	if (obj) {
		obj->AutoRelease();
	}
	return obj;
}

Object::Object() : _referenceCount(1) {}

Object::~Object() {}

std::size_t Object::GetReferenceCount() const {
	return _referenceCount;
}

void Object::Retain() {
	++_referenceCount;
}

void Object::Release() {
	--_referenceCount;
	if (_referenceCount == 0) {
		delete this;
	}
}

void Object::AutoRelease() {
	PoolManager::Instance()->GetCurrentPool()->AddObject(this);
}

} // namespace EngineS