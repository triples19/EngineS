#include "GraphicsAPI/RenderDevice.hpp"
#include "Base/Macros.hpp"
#include "GraphicsAPI/OpenGL/RenderDeviceOpenGL.hpp"

#include <memory>

namespace EngineS {

static RenderDevice* s_SharedInstance;

RenderDevice* RenderDevice::Instance() {
    if (!s_SharedInstance) {
        s_SharedInstance = new (std::nothrow) RenderDeviceOpenGL;
        ES_ASSERT_NOMSG(s_SharedInstance != nullptr);
    }
    return s_SharedInstance;
}

} // namespace EngineS
