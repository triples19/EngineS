#include "RenderSystem.hpp"

#include "Base/Hash.hpp"
#include "Base/Macros.hpp"
#include "DeviceInfo.hpp"
#include "Function/Camera.hpp"
#include "Function/GameObject.hpp"
#include "Function/SceneManager.hpp"
#include "Function/Transform2D.hpp"
#include "Material2D.hpp"
#include "Math/Math.hpp"
#include "Program.hpp"
#include "SpriteRenderer.hpp"
#include "Texture2D.hpp"
#include "WindowSystem.hpp"

namespace EngineS {

static RenderSystem* s_SharedInstance;

RenderSystem* RenderSystem::Instance() {
    if (!s_SharedInstance) {
        s_SharedInstance = new (std::nothrow) RenderSystem;
        ES_ASSERT_NOMSG(s_SharedInstance != nullptr);
    }
    return s_SharedInstance;
}

RenderSystem::RenderSystem()  = default;
RenderSystem::~RenderSystem() = default;

void RenderSystem::Initialize() {
    _window = WindowSystem::Instance()->GetWindow();

    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
        LOG_FATAL("Failed to initialize GLAD");
        return;
    }

    LOG_INFO("Initializing RenderSystem (OpenGL)");
    LOG_INFO("Vendor:\t{}", _deviceInfo.GetVendor());
    LOG_INFO("Version:\t{}", _deviceInfo.GetVersion());
    LOG_INFO("Renderer:\t{}", _deviceInfo.GetRenderer());

    WindowSystem::Instance()->RegisterOnWindowSizeFunc([](int w, int h) { glViewport(0, 0, w, h); });

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    auto resourceManager = ResourceManager::Instance();
    _programHandle       = resourceManager->GetHandle<Program>("sprite.glsl");
    resourceManager->LoadResource(_programHandle);
    resourceManager->AddWatch(_programHandle);
}

void RenderSystem::Update() {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    auto* scene  = SceneManager::Instance()->GetCurrentScene();
    auto* camera = scene->GetMainCamera();

    _batches.clear();

    scene->GetRootTransform()->Visit(Matrix4x4::Identity, [](GameObject* gameObject, const Matrix4x4& model) {
        if (gameObject->renderer) {
            gameObject->renderer->Render(model);
        }
    });

    for (auto& [id, batch] : _batches) {
        batch.Draw();
    }

    glfwSwapBuffers(_window);
}

void RenderSystem::AddToBatch(std::shared_ptr<Material2D> material,
                              const Matrix4x4&            modelMat,
                              const Vector2&              anchor,
                              const Color4F&              color) {
    auto iter = _batches.find(material->GetID());
    if (iter == _batches.end()) {
        iter = _batches.try_emplace(material->GetID(), material).first;
    }
    auto& batch = iter->second;
    batch.Add(modelMat, anchor, color);
}

std::shared_ptr<Material2D> RenderSystem::GetOrCreateMaterial(std::shared_ptr<Program>   program,
                                                              std::shared_ptr<Texture2D> texture) {
    hash32 hash = 0;
    HashCombine(hash, program->GetID(), texture->GetID());
    auto iter = _materials.find(hash);
    if (iter == _materials.end()) {
        iter = _materials.try_emplace(hash, std::make_shared<Material2D>(program, texture)).first;
    }
    return iter->second;
}

} // namespace EngineS