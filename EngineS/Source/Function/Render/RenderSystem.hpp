#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

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
	GLFWwindow* _window;
};

} // namespace EngineS
