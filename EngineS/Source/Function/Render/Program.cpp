#include "Program.hpp"

#include "Core/Base/Macros.hpp"
#include "Function/Render/Shader.hpp"

namespace EngineS {

Resource* ProgramLoader::CreateResource(const fs::path& path) const {
	auto src			= ReadString(path);
	auto vertexShader	= std::make_shared<Shader>(ShaderStage::Vertex);
	auto fragmentShader = std::make_shared<Shader>(ShaderStage::Fragment);
	vertexShader->Compile({"#version 330 core\n", "#define VERTEX\n", src});
	fragmentShader->Compile({"#version 330 core\n", "#define FRAGMENT\n", src});
	auto program = new Program(vertexShader, fragmentShader);
	program->Link();
	return program;
}

void ProgramLoader::ReloadResource(std::shared_ptr<Resource>& resource, const fs::path& path) const {}

Program::Program(std::shared_ptr<Shader> vertexShaderModule, std::shared_ptr<Shader> fragShaderModule) :
	_vertexShaderModule {vertexShaderModule}, _fragmentShaderModule {fragShaderModule} {
	_program		= glCreateProgram();
	auto vertShader = _vertexShaderModule->GetShader();
	auto fragShader = _fragmentShaderModule->GetShader();
	glAttachShader(_program, vertShader);
	glAttachShader(_program, fragShader);
}

void Program::Use() const {
	glUseProgram(_program);
}

void Program::Link() {
	glLinkProgram(_program);

	GLint status = 0;
	glGetProgramiv(_program, GL_LINK_STATUS, &status);
	if (status == GL_FALSE) {
		LOG_ERROR("Failed to link program");
		glDeleteProgram(_program);
		_program = 0;
	}
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