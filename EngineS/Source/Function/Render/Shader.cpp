#include "Shader.hpp"

#include "Core/Base/Macros.hpp"

namespace EngineS {

Resource* ShaderLoader::CreateResource(const fs::path& path) const {
	ShaderStage stage;
	if (path.extension() == ".frag")
		stage = ShaderStage::Fragment;
	else
		stage = ShaderStage::Vertex;
	return new Shader(stage, ReadString(path));
}

Shader::Shader(ShaderStage stage, const std::string& src) {
	GLenum shaderType;
	switch (stage) {
		case ShaderStage::Vertex:
			shaderType = GL_VERTEX_SHADER;
			break;
		case ShaderStage::Fragment:
			shaderType = GL_FRAGMENT_SHADER;
			break;
	}

	const GLchar* srcPtr = reinterpret_cast<const GLchar*>(src.c_str());

	_shader = glCreateShader(shaderType);
	glShaderSource(_shader, 1, &srcPtr, nullptr);
	glCompileShader(_shader);

	GLint status = 0;
	glGetShaderiv(_shader, GL_COMPILE_STATUS, &status);
	if (!status) {
		char infoLog[1024];
		glGetShaderInfoLog(_shader, 1024, nullptr, infoLog);
		LOG_ERROR("Failed to compile shader:\n{}", src);
		LOG_ERROR("{}", infoLog);
	}
}

Shader::~Shader() {
	if (_shader) {
		glDeleteShader(_shader);
		_shader = 0;
	}
}

} // namespace EngineS