#include "Render/OpenGL/ShaderOpenGL.hpp"
#include "Render/OpenGL/UtilsOpenGL.hpp"

namespace EngineS {

ShaderOpenGL::~ShaderOpenGL() {
    if (_shader) {
        glDeleteShader(_shader);
        _shader = 0;
    }
}

bool ShaderOpenGL::CompileInternal(ShaderStage stage, const char** src, std::size_t size) {
    if (_shader) {
        glDeleteShader(_shader);
    }

    _shader = glCreateShader(UtilsOpenGL::ConvertShaderStage(stage));

    glShaderSource(_shader, size, src, nullptr);
    glCompileShader(_shader);
    GLint status = 0;
    glGetShaderiv(_shader, GL_COMPILE_STATUS, &status);
    if (status == GL_FALSE) {
        GLint logLength;
        glGetShaderiv(_shader, GL_INFO_LOG_LENGTH, &logLength);
        std::string log;
        log.resize(logLength);
        glGetShaderInfoLog(_shader, logLength, nullptr, log.data());
        Logger::Error("Failed to compile shader\n{}", log);
        return false;
    }
    UtilsOpenGL::CheckError();
    return true;
}

} // namespace EngineS