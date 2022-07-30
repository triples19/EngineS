#pragma once

#include <glad/glad.h>

#include <optional>
#include <string>

#include "Core/Math/MathHeaders.hpp"

namespace EngineS {

class Shader {
  public:
	Shader() = default;

	void Use() const;

	void Compile(const std::string&				   vertexSource,
				 const std::string&				   fragmentSource,
				 const std::optional<std::string>& geometrySource = std::nullopt);

	void Set(const std::string& name, bool value) const;
	void Set(const std::string& name, int value) const;
	void Set(const std::string& name, float value) const;
	void Set(const std::string& name, const Vector2& value) const;
	void Set(const std::string& name, float x, float y) const;
	void Set(const std::string& name, const Vector3& value) const;
	void Set(const std::string& name, float x, float y, float z) const;
	void Set(const std::string& name, const Vector4& value) const;
	void Set(const std::string& name, float x, float y, float z, float w);
	void Set(const std::string& name, const Matrix3x3& mat) const;
	void Set(const std::string& name, const Matrix4x4& mat) const;

  private:
	void CheckCompileErrors(GLuint shader, std::string type);

  private:
	unsigned int _id;
};

} // namespace EngineS
