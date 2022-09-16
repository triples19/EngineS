#pragma once

#include "Platform/GLCommon.hpp"
#include "Program.hpp"
#include "Resource/ResourceManager.hpp"
#include "SpriteBatch.hpp"

#include <GLFW/glfw3.h>
#include <memory>
#include <utility>

namespace EngineS {

class Material2D;
class Transform2D;
class Program;
class Texture2D;

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

	void AddToBatch(std::shared_ptr<Material2D> material, const Transform2D* transform);

	std::shared_ptr<Material2D> GetOrCreateMaterial(std::shared_ptr<Program>   program,
													std::shared_ptr<Texture2D> texture);

  private:
	ResourceHandle<Program> _programHandle;
	GLFWwindow*				_window;

	std::unordered_map<std::size_t, std::shared_ptr<Material2D>> _materials;
	std::unordered_map<unsigned int, SpriteBatch>				 _batches;
};

} // namespace EngineS
