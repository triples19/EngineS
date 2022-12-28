#pragma once

#include <vector>

namespace EngineS {

class AutoReleasePool;

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