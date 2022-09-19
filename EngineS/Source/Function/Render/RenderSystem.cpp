#include "RenderSystem.hpp"

#include "Core/Base/Hash.hpp"
#include "Core/Base/Macros.hpp"
#include "Core/Math/MathHeaders.hpp"
#include "Function/Global/Global.hpp"
#include "Function/Object/Component/Camera.hpp"
#include "Function/Object/Component/Transform2D.hpp"
#include "Function/Object/GameObject.hpp"
#include "Function/Render/Material2D.hpp"
#include "Function/Render/Program.hpp"
#include "Function/Render/SpriteRenderer.hpp"
#include "Function/Render/Texture2D.hpp"
#include "Function/Render/WindowSystem.hpp"
#include "Function/Scene/SceneManager.hpp"

namespace EngineS {

static RenderSystem* s_SharedInstance;

RenderSystem* RenderSystem::Instance() {
	if (!s_SharedInstance) {
		s_SharedInstance = new (std::nothrow) RenderSystem;
		assert(s_SharedInstance != nullptr);
	}
	return s_SharedInstance;
}

void RenderSystem::PreWindowInitialize() {
	if (!glfwInit()) {
		LOG_FATAL("Failed to initialize GLFW");
		return;
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
}

void RenderSystem::Initialize() {
	_window = WindowSystem::Instance()->GetWindow();

	if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
		LOG_FATAL("Failed to initialize GLAD");
		return;
	}

	WindowSystem::Instance()->RegisterOnWindowSizeFunc([](int w, int h) { glViewport(0, 0, w, h); });

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	auto resourceManager = ResourceManager::Instance();
	_programHandle		 = resourceManager->GetHandle<Program>("sprite.glsl");
	resourceManager->LoadResource(_programHandle);
	resourceManager->AddWatch(_programHandle);
}

void RenderSystem::Update() {
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	auto* scene	 = SceneManager::Instance()->GetCurrentScene();
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

void RenderSystem::AddToBatch(std::shared_ptr<Material2D> material, const Matrix4x4& modelMat, const Vector2& anchor) {
	auto iter = _batches.find(material->GetID());
	if (iter == _batches.end()) {
		iter = _batches.try_emplace(material->GetID(), material).first;
	}
	auto& batch = iter->second;
	batch.Add(modelMat, anchor);
}

std::shared_ptr<Material2D> RenderSystem::GetOrCreateMaterial(std::shared_ptr<Program>	 program,
															  std::shared_ptr<Texture2D> texture) {
	std::size_t hash = 0;
	HashCombine(hash, program->GetID(), texture->GetID());
	auto iter = _materials.find(hash);
	if (iter == _materials.end()) {
		iter = _materials.try_emplace(hash, std::make_shared<Material2D>(program, texture)).first;
	}
	return iter->second;
}

} // namespace EngineS