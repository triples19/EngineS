#pragma once

#include "Core/Base/Macros.hpp"
#include "Platform/GLCommon.hpp"
#include "Resource/Resource.hpp"
#include "Resource/ResourceManager.hpp"
#include "Types.hpp"

#include <string>

namespace EngineS {

class Shader : public Resource {
  public:
	Shader(ShaderStage stage, const std::string& src);
	~Shader();

	GLuint GetShader() const { return _shader; }

  private:
	GLuint _shader {0};
};

class ShaderLoader : public ResourceLoader {
  public:
	virtual Resource*	CreateResource(const fs::path& path) const;
	virtual std::string GetName() const { return "ShaderLoader"; }
};

} // namespace EngineS
