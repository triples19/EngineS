#include "Render/RenderSystem.hpp"
#include "Base/Hash.hpp"
#include "Base/Macros.hpp"
#include "Function/Camera.hpp"
#include "Function/GameObject.hpp"
#include "Function/Scene.hpp"
#include "Function/SceneManager.hpp"
#include "Function/Transform2D.hpp"
#include "Math/Math.hpp"
#include "Render/DeviceInfo.hpp"
#include "Render/DrawList.hpp"
#include "Render/Framebuffer.hpp"
#include "Render/Material2D.hpp"
#include "Render/Program.hpp"
#include "Render/RenderDevice.hpp"
#include "Render/SpriteRenderer.hpp"
#include "Render/Texture2D.hpp"
#include "Render/WindowSystem.hpp"
#include "Resource/ResourceManager.hpp"

namespace EngineS {

static RenderSystem* s_SharedInstance;

RenderSystem* RenderSystem::Instance() {
    if (!s_SharedInstance) {
        s_SharedInstance = new (std::nothrow) RenderSystem;
        ES_ASSERT_NOMSG(s_SharedInstance != nullptr);
    }
    return s_SharedInstance;
}

RenderSystem::RenderSystem() = default;

RenderSystem::~RenderSystem() {
    if (_colorTex)
        _colorTex->Release();
    if (_depthTex)
        _depthTex->Release();
    if (_framebuffer)
        _framebuffer->Release();
}

void RenderSystem::Initialize() {
    // Must initialize render device first!
    auto device = RenderDevice::Instance();

    Logger::Info("Initializing RenderSystem (OpenGL)");
    Logger::Info("Vendor:\t{}", _deviceInfo.GetVendor());
    Logger::Info("Version:\t{}", _deviceInfo.GetVersion());
    Logger::Info("Renderer:\t{}", _deviceInfo.GetRenderer());

    WindowSystem::Instance()->RegisterOnWindowSizeFunc([this](u32 w, u32 h) { this->OnWindowSizeChange(w, h); });

    auto [width, height] = WindowSystem::Instance()->GetFramebufferSize();

    _colorTex = device->CreateTexture2D();
    _colorTex->Init(TextureDescriptor {
        .textureType       = TextureType::Texture2D,
        .textureFormat     = PixelFormat::RGBA8888,
        .textureUsage      = TextureUsage::RenderTarget,
        .width             = width,
        .height            = height,
        .samplerDescriptor = {},
        .data              = nullptr,
    });
    _colorTex->Retain();

    //    _depthTex = device->CreateTexture2D();
    //    _depthTex->Init(TextureDescriptor {
    //        .textureType       = TextureType::Texture2D,
    //        .textureFormat     = PixelFormat::D16,
    //        .textureUsage      = TextureUsage::RenderTarget,
    //        .width             = width,
    //        .height            = height,
    //        .samplerDescriptor = {},
    //    });

    _framebuffer = device->CreateFramebuffer(FramebufferDescriptor {
        .colorAttachments = {Attachment {.texture = _colorTex}},
    });
    _framebuffer->Retain();
}

void RenderSystem::Update() {
    auto device = RenderDevice::Instance();

    auto drawList = device->CreateDrawList();
    drawList->Begin(RenderPassDescriptor {
        .framebuffer     = _framebuffer,
        .clearColor      = true,
        .clearColorValue = {0.2f, 0.3f, 0.3f, 1.0f},
    });

    auto [fbWidth, fbHeight] = WindowSystem::Instance()->GetFramebufferSize();
    drawList->SetViewport(0, 0, fbWidth, fbHeight);

    auto* scene  = SceneManager::Instance()->GetCurrentScene();
    auto* camera = scene->GetMainCamera();

    scene->GetRootTransform()->Visit(Matrix4x4::Identity, [drawList](GameObject* gameObject, const Matrix4x4& model) {
        auto renderer = gameObject->GetComponent<Renderer>();
        if (renderer) {
            renderer->Render(model, drawList);
        }
    });

    drawList->End();

    WindowSystem::Instance()->SwapBuffers();
}

void RenderSystem::OnWindowSizeChange(u32 width, u32 height) {
    if (_colorTex)
        _colorTex->UpdateData(nullptr, width, height);
    if (_depthTex)
        _depthTex->UpdateData(nullptr, width, height);
}

} // namespace EngineS