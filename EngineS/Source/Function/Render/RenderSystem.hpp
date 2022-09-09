#pragma once

#include "Platform/GLCommon.hpp"
#include "Program.hpp"
#include "Resource/ResourceManager.hpp"

#include <GLFW/glfw3.h>
#include <memory>

namespace EngineS {

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
	ResourceHandle<Program> _programHandle;
	GLFWwindow*				_window;
};

} // namespace EngineS
