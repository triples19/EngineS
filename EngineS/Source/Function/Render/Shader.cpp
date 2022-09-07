#include "Shader.hpp"

#include "Core/Base/Macros.hpp"

#include <algorithm>

namespace EngineS {

Shader::Shader(ShaderStage stage) {
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
}

Shader::~Shader() {
	if (_shader) {
		glDeleteShader(_shader);
		_shader = 0;
	}
}

void Shader::Compile(const std::string& src) {
	const GLchar* srcPtr = reinterpret_cast<const GLchar*>(src.c_str());
	Compile(&srcPtr, 1);
}

void Shader::Compile(const std::vector<std::string>& src) {
	auto ptr = new const GLchar*[src.size()];
	std::transform(src.begin(), src.end(), ptr, [](const std::string& str) { return str.c_str(); });
	Compile(ptr, src.size());
	delete[] ptr;
}

void Shader::Compile(const GLchar** src, std::size_t size) {
	glShaderSource(_shader, size, src, nullptr);
	glCompileShader(_shader);
	GLint status = 0;
	glGetShaderiv(_shader, GL_COMPILE_STATUS, &status);
	if (!status) {
		char infoLog[1024];
		glGetShaderInfoLog(_shader, 1024, nullptr, infoLog);
		LOG_ERROR("Failed to compile shader");
		LOG_ERROR("{}", infoLog);
	}
}

} // namespace EngineS