#include "Shader.hpp"

#include "Core/Base/Macros.hpp"

namespace EngineS {

void Shader::Use() const {
	glUseProgram(_id);
}

void Shader::Compile(const std::string&				   vertexSource,
					 const std::string&				   fragmentSource,
					 const std::optional<std::string>& geometrySource) {
	unsigned int vertexShader, fragmentShader, geometryShader;

	const char* vertexShaderCStr = vertexSource.c_str();
	vertexShader				 = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderCStr, nullptr);
	glCompileShader(vertexShader);
	CheckCompileErrors(vertexShader, "Vertex");

	const char* fragmentShaderCStr = fragmentSource.c_str();
	fragmentShader				   = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderCStr, nullptr);
	glCompileShader(fragmentShader);
	CheckCompileErrors(fragmentShader, "Fragment");

	if (geometrySource) {
		const char* geometryShaderCStr = geometrySource->c_str();
		geometryShader				   = glCreateShader(GL_GEOMETRY_SHADER);
		glShaderSource(geometryShader, 1, &geometryShaderCStr, nullptr);
		glCompileShader(geometryShader);
		CheckCompileErrors(geometryShader, "Geometry");
	}

	_id = glCreateProgram();
	glAttachShader(_id, vertexShader);
	glAttachShader(_id, fragmentShader);
	if (geometrySource)
		glAttachShader(_id, geometryShader);
	glLinkProgram(_id);
	CheckCompileErrors(_id, "Program");

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	if (geometrySource)
		glDeleteShader(geometryShader);
}

void Shader::CheckCompileErrors(GLuint shader, std::string type) {
	int	 success;
	char infoLog[1024];
	if (type != "Program") {
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(shader, 1024, nullptr, infoLog);
			LOG_ERROR("Shader compilation error of type: {0}\n{1}", type, infoLog);
		}
	} else {
		glGetProgramiv(shader, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(shader, 1024, nullptr, infoLog);
			LOG_ERROR("Shader program linking error of type: {0}\n{1}", type, infoLog);
		}
	}
}

void Shader::Set(const std::string& name, bool value) const {
	glUniform1i(glGetUniformLocation(_id, name.c_str()), static_cast<int>(value));
}

void Shader::Set(const std::string& name, int value) const {
	glUniform1i(glGetUniformLocation(_id, name.c_str()), value);
}

void Shader::Set(const std::string& name, float value) const {
	glUniform1f(glGetUniformLocation(_id, name.c_str()), value);
}

void Shader::Set(const std::string& name, const Vector2& value) const {
	glUniform2fv(glGetUniformLocation(_id, name.c_str()), 1, value.Data());
}

void Shader::Set(const std::string& name, float x, float y) const {
	glUniform2f(glGetUniformLocation(_id, name.c_str()), x, y);
}

void Shader::Set(const std::string& name, const Vector3& value) const {
	glUniform3fv(glGetUniformLocation(_id, name.c_str()), 1, value.Data());
}

void Shader::Set(const std::string& name, float x, float y, float z) const {
	glUniform3f(glGetUniformLocation(_id, name.c_str()), x, y, z);
}

void Shader::Set(const std::string& name, const Vector4& value) const {
	glUniform4fv(glGetUniformLocation(_id, name.c_str()), 1, value.Data());
}

void Shader::Set(const std::string& name, float x, float y, float z, float w) {
	glUniform4f(glGetUniformLocation(_id, name.c_str()), x, y, z, w);
}

void Shader::Set(const std::string& name, const Matrix3x3& mat) const {
	glUniformMatrix3fv(glGetUniformLocation(_id, name.c_str()), 1, GL_TRUE, mat.Data());
}

void Shader::Set(const std::string& name, const Matrix4x4& mat) const {
	glUniformMatrix4fv(glGetUniformLocation(_id, name.c_str()), 1, GL_TRUE, mat.Data());
}

} // namespace EngineS