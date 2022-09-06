#pragma once

#include "Platform/GLCommon.hpp"

#include <GLFW/glfw3.h>
#include <memory>

namespace EngineS {

class Program;

class RenderSystem {
  public:
	RenderSystem()	= default;
	~RenderSystem() = default;

	/**
	 * Called before glfw window is initialized
	 */
	void PreWindowInitialize();

	/**
	 * Called after glfw window is initialized
	 */
	void Initialize();

	void Update();

  private:
	std::shared_ptr<Program> _program;
	GLFWwindow*				 _window;
};

} // namespace EngineS
