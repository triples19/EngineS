#include "Graphics/WindowSystem.hpp"
#include "Base/Macros.hpp"
#include "IO/Logger.hpp"

#include <GLFW/glfw3.h>

#define GLFW_CALLBACK(functionName)                                                          \
    [](GLFWwindow* window, auto... args) {                                                   \
        static_cast<WindowSystem*>(glfwGetWindowUserPointer(window))->functionName(args...); \
    }

namespace EngineS {

static WindowSystem* s_SharedInstance;

WindowSystem* WindowSystem::Instance() {
    if (!s_SharedInstance) {
        s_SharedInstance = new (std::nothrow) WindowSystem;
        ES_ASSERT_NOMSG(s_SharedInstance != nullptr);
    }
    return s_SharedInstance;
}

WindowSystem::~WindowSystem() {
    glfwDestroyWindow(_window);
    glfwTerminate();
}

void WindowSystem::Initialize() {
    Logger::Info("Initializing WindowSystem (GLFW)");

    if (!glfwInit()) {
        Logger::Error("Failed to initialize GLFW");
        return;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    _window = glfwCreateWindow(_width, _height, _title.c_str(), nullptr, nullptr);
    if (!_window) {
        Logger::Error("Failed to create GLFW window");
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

void WindowSystem::SwapBuffers() const {
    glfwSwapBuffers(_window);
}

bool WindowSystem::ShouldClose() const {
    return glfwWindowShouldClose(_window);
}

void WindowSystem::SetTitle(const std::string& title) {
    glfwSetWindowTitle(_window, title.c_str());
}

void WindowSystem::SetWindowSize(u32 width, u32 height) {
    _width  = width;
    _height = height;
    glfwSetWindowSize(_window, width, height);
}

GLFWwindow* WindowSystem::GetWindow() const {
    return _window;
}

std::tuple<u32, u32> WindowSystem::GetWindowSize() const {
    return {_width, _height};
}

} // namespace EngineS
