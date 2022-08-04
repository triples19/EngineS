#include "RenderSystem.hpp"
#include "Core/Base/Macros.hpp"
#include "Core/Math/MathHeaders.hpp"
#include "Function/Global/Global.hpp"
#include "Function/Object/Component/Transform2D.hpp"
#include "Function/Object/GameObject.hpp"
#include "Function/Render/Shader.hpp"
#include "Function/Render/SpriteRenderer.hpp"
#include "Function/Render/Texture2D.hpp"
#include "Function/Render/WindowSystem.hpp"
#include "Function/Scene/SceneManager.hpp"
#include "Resource/ResourceManager.hpp"

namespace EngineS {

void RenderSystem::PreWindowInitialize() {
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

void RenderSystem::Initialize() {
	_window = Global::Instance()->windowSystem->GetWindow();

	if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
		LOG_FATAL("Failed to initialize GLAD");
		return;
	}

	Global::Instance()->windowSystem->RegisterOnWindowSizeFunc([](int w, int h) { glViewport(0, 0, w, h); });
}

void RenderSystem::Update() {
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	auto shader = Global::Instance()->resourceManager->GetDefaultSpriteShader();
	shader->Use();
	shader->Set("image", 0);
	shader->Set("projection", Orthographic(1280.0f, 920.0f, -1.0f, 1.0f));

	auto* scene = Global::Instance()->sceneManager->GetCurrentScene();
	for (auto& obj : scene->GetGameObjects()) {
		obj->renderer->Render();
	}

	glfwSwapBuffers(_window);
}

} // namespace EngineS