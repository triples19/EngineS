#pragma once

#include "Core/Math/MathHeaders.hpp"
#include "Platform/GLCommon.hpp"
#include "Resource/Resource.hpp"
#include "Shader.hpp"

#include <memory>
#include <optional>
#include <string>

namespace EngineS {

class Program : public Resource {
	friend class ProgramLoader;

  public:
	Program(std::shared_ptr<Shader> vertexShaderModule, std::shared_ptr<Shader> fragShaderModule);

	void Use() const;

	void Link();

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
	GLuint _program {0};

	std::shared_ptr<Shader> _vertexShaderModule;
	std::shared_ptr<Shader> _fragmentShaderModule;
};

class ProgramLoader : public ResourceLoader {
  public:
	virtual Resource*	CreateResource(const fs::path& path) const;
	virtual void		ReloadResource(std::shared_ptr<Resource>& resource, const fs::path& path) const;
	virtual std::string GetName() const { return "ProgramLoader"; }
};

} // namespace EngineS
