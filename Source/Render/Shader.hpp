#pragma once

#include "Base/Macros.hpp"
#include "Platform/GLCommon.hpp"
#include "Resource/Resource.hpp"
#include "Resource/ResourceManager.hpp"

#include <string>
#include <vector>

namespace EngineS {

enum class ShaderStage : uint32_t { Vertex, Fragment };

class Shader : public Resource {
  public:
	Shader(ShaderStage stage);
	~Shader();

	GLuint GetShader() const { return _shader; }

	void Compile(const std::string& src);
	void Compile(const std::vector<std::string>& src);

  private:
	void Compile(const GLchar** src, std::size_t size);

  private:
	GLuint		_shader {0};
	ShaderStage _stage;
};

} // namespace EngineS
