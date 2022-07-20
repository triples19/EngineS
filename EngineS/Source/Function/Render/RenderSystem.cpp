#include "RenderSystem.hpp"
#include "Core/Base/Macros.hpp"
#include "Function/Global/Global.hpp"
#include "Function/Render/WindowSystem.hpp"

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

	glfwSwapBuffers(_window);
}

} // namespace EngineS