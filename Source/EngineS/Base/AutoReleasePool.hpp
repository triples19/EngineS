#pragma once

#include <vector>

namespace EngineS {

class Ref;

class AutoReleasePool {
  public:
    AutoReleasePool();
    ~AutoReleasePool();

    void AddObject(Ref* obj);

    void Clear();

  private:
    std::vector<Ref*> _managedObjects;
};

} // namespace EngineS