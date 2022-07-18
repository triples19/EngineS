#include "WindowSystem.hpp"
#include "Core/Base/Macros.hpp"
#include "Core/Logging/LoggingSystem.hpp"

#define GLFW_CALLBACK(functionName)                                                          \
	[](GLFWwindow* window, auto... args) {                                                   \
		static_cast<WindowSystem*>(glfwGetWindowUserPointer(window))->functionName(args...); \
	}

namespace EngineS {

WindowSystem::~WindowSystem() {
	glfwDestroyWindow(_window);
	glfwTerminate();
}

void WindowSystem::Initialize(int width, int height, const char* title) {
	LOG_INFO("Initialzing WindowSystem (GLFW)");

	if (!glfwInit()) {
		LOG_FATAL("Failed to initialize GLFW");
		return;
	}

	_width	= width;
	_height = height;

	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	_window = glfwCreateWindow(width, height, title, nullptr, nullptr);
	if (!_window) {
		LOG_FATAL("Failed to create GLFW window");
		glfwTerminate();
		return;
	}

	glfwSetWindowUserPointer(_window, this);
	glfwSetKeyCallback(_window, GLFW_CALLBACK(OnKey));
	glfwSetCharCallback(_window, GLFW_CALLBACK(OnChar));
	glfwSetCharModsCallback(_window, GLFW_CALLBACK(OnCharMods));
	glfwSetMouseButtonCallback(_window, GLFW_CALLBACK(OnMouseButton));
	glfwSetCursorPosCallback(_window, GLFW_CALLBACK(OnCursorPos));
	glfwSetCursorEnterCallback(_window, GLFW_CALLBACK(OnCursorEnter));
	glfwSetScrollCallback(_window, GLFW_CALLBACK(OnScroll));
	glfwSetDropCallback(_window, GLFW_CALLBACK(OnDrop));
	glfwSetWindowSizeCallback(_window, GLFW_CALLBACK(OnWindowSize));
	glfwSetWindowCloseCallback(_window, GLFW_CALLBACK(OnWindowClose));

	glfwSetInputMode(_window, GLFW_RAW_MOUSE_MOTION, GLFW_FALSE);
}

void WindowSystem::PollEvents() const {
	glfwPollEvents();
}

bool WindowSystem::ShouldClose() const {
	return glfwWindowShouldClose(_window);
}

void WindowSystem::SetTitle(const std::string& title) {
	glfwSetWindowTitle(_window, title.c_str());
}

} // namespace EngineS
