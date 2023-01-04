#include "Render/Program.hpp"
#include "Base/Macros.hpp"
#include "IO/FileUtils.hpp"
#include "Render/Shader.hpp"

namespace EngineS {

Program::~Program() {
    if (_vertexShader)
        _vertexShader->Release();
    if (_fragmentShader)
        _fragmentShader->Release();
}

bool Program::Load(const std::filesystem::path& path) {
    if (_vertexShader)
        _vertexShader->Release();
    if (_fragmentShader)
        _fragmentShader->Release();

    auto src = FileUtils::ReadFileStr(path);

    _vertexShader = new Shader;
    if (!_vertexShader->Compile(ShaderStage::Vertex, {"#version 330 core\n", "#define VERTEX\n", src})) {
        return false;
    }
    _vertexShader->Retain();

    _fragmentShader = new Shader;
    if (!_fragmentShader->Compile(ShaderStage::Fragment, {"#version 330 core\n", "#define FRAGMENT\n", src})) {
        return false;
    }
    _fragmentShader->Retain();

    _program = glCreateProgram();
    glAttachShader(_program, _fragmentShader->GetShader());
    glAttachShader(_program, _vertexShader->GetShader());

    glLinkProgram(_program);

    GLint status = 0;
    glGetProgramiv(_program, GL_LINK_STATUS, &status);
    if (status == GL_FALSE) {
        char infoLog[1024];
        glGetProgramInfoLog(_program, 1024, nullptr, infoLog);
        LOG_ERROR("Failed to link program\n{}", infoLog);
        return false;
    }
    return true;
}

void Program::Use() const {
    glUseProgram(_program);
}

void Program::Set(const std::string& name, bool value) const {
    glUniform1i(glGetUniformLocation(_program, name.c_str()), static_cast<int>(value));
}

void Program::Set(const std::string& name, int value) const {
    glUniform1i(glGetUniformLocation(_program, name.c_str()), value);
}

void Program::Set(const std::string& name, float value) const {
    glUniform1f(glGetUniformLocation(_program, name.c_str()), value);
}

void Program::Set(const std::string& name, const Vector2& value) const {
    glUniform2fv(glGetUniformLocation(_program, name.c_str()), 1, value.Data());
}

void Program::Set(const std::string& name, float x, float y) const {
    glUniform2f(glGetUniformLocation(_program, name.c_str()), x, y);
}

void Program::Set(const std::string& name, const Vector3& value) const {
    glUniform3fv(glGetUniformLocation(_program, name.c_str()), 1, value.Data());
}

void Program::Set(const std::string& name, float x, float y, float z) const {
    glUniform3f(glGetUniformLocation(_program, name.c_str()), x, y, z);
}

void Program::Set(const std::string& name, const Vector4& value) const {
    glUniform4fv(glGetUniformLocation(_program, name.c_str()), 1, value.Data());
}

void Program::Set(const std::string& name, float x, float y, float z, float w) {
    glUniform4f(glGetUniformLocation(_program, name.c_str()), x, y, z, w);
}

void Program::Set(const std::string& name, const Matrix3x3& mat) const {
    glUniformMatrix3fv(glGetUniformLocation(_program, name.c_str()), 1, GL_TRUE, mat.Data());
}

void Program::Set(const std::string& name, const Matrix4x4& mat) const {
    glUniformMatrix4fv(glGetUniformLocation(_program, name.c_str()), 1, GL_TRUE, mat.Data());
}

} // namespace EngineS