#pragma once

namespace EngineS {

class DeviceInfo {
  public:
    const char* GetVendor() const;
    const char* GetRenderer() const;
    const char* GetVersion() const;
};

} // namespace EngineS