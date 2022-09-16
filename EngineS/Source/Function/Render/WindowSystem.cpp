#include "WindowSystem.hpp"
#include "Core/Base/Macros.hpp"
#include "Core/Logging/LoggingSystem.hpp"

#define GLFW_CALLBACK(functionName)                                                          \
	[](GLFWwindow* window, auto... args) {                                                   \
		static_cast<WindowSystem*>(glfwGetWindowUserPointer(window))->functionName(args...); \
	}

namespace EngineS {

static WindowSystem* s_SharedInstance;

WindowSystem* WindowSystem::Instance() {
	if (!s_SharedInstance) {
		s_SharedInstance = new (std::nothrow) WindowSystem;
		assert(s_SharedInstance != nullptr);
	}
	return s_SharedInstance;
}

WindowSystem::~WindowSystem() {
	glfwDestroyWindow(_window);
	glfwTerminate();
}

void WindowSystem::Initialize(int width, int height, const char* title) {
	LOG_INFO("Initialzing WindowSystem (GLFW)");

	_width	= width;
	_height = height;

	_window = glfwCreateWindow(width, height, title, nullptr, nullptr);
	if (!_window) {
		LOG_FATAL("Failed to create GLFW window");
		glfwTerminate();
		return;
	}
	glfwMakeContextCurrent(_window);

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
