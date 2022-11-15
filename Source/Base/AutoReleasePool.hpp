#pragma once

#include "Object.hpp"

#include <vector>

namespace EngineS {

class AutoReleasePool {
  public:
	AutoReleasePool();
	~AutoReleasePool();

	void AddObject(Object* obj);

	void Clear();

  private:
	std::vector<Object*> _managedObjects;
};

} // namespace EngineS