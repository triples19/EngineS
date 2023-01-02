#include "Shader.hpp"

#include "Base/Macros.hpp"

#include <algorithm>

namespace EngineS {

Shader::~Shader() {
    if (_shader) {
        glDeleteShader(_shader);
        _shader = 0;
    }
}

bool Shader::Compile(ShaderStage stage, const std::string& src) {
    const GLchar* srcPtr = reinterpret_cast<const GLchar*>(src.c_str());
    return CompileInternal(stage, &srcPtr, 1);
}

bool Shader::Compile(ShaderStage stage, const std::vector<std::string>& src) {
    auto ptr = new const GLchar*[src.size()];
    std::transform(src.begin(), src.end(), ptr, [](const std::string& str) { return str.c_str(); });
    if (!CompileInternal(stage, ptr, src.size()))
        return false;
    delete[] ptr;
    return true;
}

bool Shader::CompileInternal(ShaderStage stage, const GLchar** src, std::size_t size) {
    if (_shader) {
        glDeleteShader(_shader);
    }

    GLenum shaderType;
    switch (stage) {
        case ShaderStage::Vertex:
            shaderType = GL_VERTEX_SHADER;
            break;
        case ShaderStage::Fragment:
            shaderType = GL_FRAGMENT_SHADER;
            break;
    }
    _shader = glCreateShader(shaderType);

    glShaderSource(_shader, size, src, nullptr);
    glCompileShader(_shader);
    GLint status = 0;
    glGetShaderiv(_shader, GL_COMPILE_STATUS, &status);
    if (!status) {
        char infoLog[1024];
        glGetShaderInfoLog(_shader, 1024, nullptr, infoLog);
        LOG_ERROR("Failed to compile shader\n{}", infoLog);
        return false;
    }
    return true;
}

} // namespace EngineS