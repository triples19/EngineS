#pragma once

#include "Platform/GLCommon.hpp"
#include "Resource/ResourceManager.hpp"

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
	ResourceHandle* _programHandle;
	GLFWwindow*		_window;
};

} // namespace EngineS
