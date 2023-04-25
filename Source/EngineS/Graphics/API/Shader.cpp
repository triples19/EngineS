#include "Shader.hpp"

#include "Core/Macros.hpp"

#include <algorithm>

namespace EngineS {

bool Shader::Compile(ShaderStage stage, const std::string& src) {
    const char* srcPtr = reinterpret_cast<const char*>(src.c_str());
    return CompileInternal(stage, &srcPtr, 1);
}

bool Shader::Compile(ShaderStage stage, const std::vector<std::string>& src) {
    auto ptr = new const char*[src.size()];
    std::transform(src.begin(), src.end(), ptr, [](const std::string& str) { return str.c_str(); });
    if (!CompileInternal(stage, ptr, src.size())) {
        delete[] ptr;
        return false;
    }
    delete[] ptr;
    return true;
}

} // namespace EngineS