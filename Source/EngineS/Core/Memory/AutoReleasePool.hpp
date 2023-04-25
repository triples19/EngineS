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

class PoolManager {
  public:
    static PoolManager* Instance();

    AutoReleasePool* GetCurrentPool() const;

    friend class AutoReleasePool;

  private:
    PoolManager();
    ~PoolManager();

    void PushPool(AutoReleasePool* pool);
    void PopPool();

  private:
    std::vector<AutoReleasePool*> _releasePools;
};

} // namespace EngineS