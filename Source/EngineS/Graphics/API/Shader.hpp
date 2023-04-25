#pragma once

#include "Core/Macros.hpp"
#include "RenderTypes.hpp"
#include "Resource/Resource.hpp"
#include "Resource/ResourceManager.hpp"

#include <string>
#include <vector>

namespace EngineS {

class Shader : public Object {
    ES_OBJECT
  public:
    bool Compile(ShaderStage stage, const std::string& src);
    bool Compile(ShaderStage stage, const std::vector<std::string>& src);

  protected:
    virtual bool CompileInternal(ShaderStage stage, const char** src, std::size_t size) = 0;

  private:
    ShaderStage _stage;
};

} // namespace EngineS
