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
    ES_OBJECT
  public:
    ~Shader();

    GLuint GetShader() const { return _shader; }

    bool Compile(ShaderStage stage, const std::string& src);
    bool Compile(ShaderStage stage, const std::vector<std::string>& src);

  private:
    bool CompileInternal(ShaderStage stage, const GLchar** src, std::size_t size);

  private:
    GLuint      _shader {0};
    ShaderStage _stage;
};

} // namespace EngineS
