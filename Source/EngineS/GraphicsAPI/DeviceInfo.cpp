#include "GraphicsAPI/DeviceInfo.hpp"

#include "glad/glad.h"

namespace EngineS {

const char* DeviceInfo::GetVendor() const {
    return reinterpret_cast<const char*>(glGetString(GL_VENDOR));
}

const char* DeviceInfo::GetRenderer() const {
    return reinterpret_cast<const char*>(glGetString(GL_RENDERER));
}

const char* DeviceInfo::GetVersion() const {
    return reinterpret_cast<const char*>(glGetString(GL_VERSION));
}

} // namespace EngineS
