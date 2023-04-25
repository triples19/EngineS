#include "ProgramOpenGL.hpp"
#include "ShaderOpenGL.hpp"
#include "UtilsOpenGL.hpp"

namespace EngineS {

ProgramOpenGL::ProgramOpenGL() {
    _program = glCreateProgram();
}

ProgramOpenGL::~ProgramOpenGL() {
    if (_program) {
        glDeleteProgram(_program);
    }
}

bool ProgramOpenGL::Link(Shader* fragShader, Shader* vertShader) {
    glAttachShader(_program, static_cast<ShaderOpenGL*>(fragShader)->GetHandler());
    glAttachShader(_program, static_cast<ShaderOpenGL*>(vertShader)->GetHandler());

    glLinkProgram(_program);

    GLint status = 0;
    glGetProgramiv(_program, GL_LINK_STATUS, &status);
    if (status == GL_FALSE) {
        GLint logLength;
        glGetProgramiv(_program, GL_INFO_LOG_LENGTH, &logLength);
        std::string log;
        log.resize(logLength);
        glGetProgramInfoLog(_program, logLength, nullptr, log.data());
        Logger::Error("Failed to link program\n{}", log);
        return false;
    }
    UtilsOpenGL::CheckError();
    return true;
}

} // namespace EngineS
