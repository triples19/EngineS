#include "RenderDevice.hpp"
#include "Core/Macros.hpp"
#include "Graphics/API/OpenGL/RenderDeviceOpenGL.hpp"

#include <memory>

namespace EngineS {

static RenderDevice* s_SharedInstance;

RenderDevice* RenderDevice::Instance() {
    if (!s_SharedInstance) {
        s_SharedInstance = new (std::nothrow) RenderDeviceOpenGL;
        ES_ASSERT(s_SharedInstance != nullptr);
    }
    return s_SharedInstance;
}

} // namespace EngineS
