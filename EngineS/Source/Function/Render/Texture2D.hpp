#pragma once

#include "Resource/Resource.hpp"

#include <glad/glad.h>

namespace EngineS {

class Texture2D : public Resource {
  public:
	unsigned int id {0};
	unsigned int width {0}, height {0};
	unsigned int internalFormat {GL_RGB};
	unsigned int imageFormat {GL_RGB};
	unsigned int wrapS {GL_REPEAT}, wrapT {GL_REPEAT};
	unsigned int filterMin {GL_LINEAR}, filterMax {GL_LINEAR};

	Texture2D() = default;

	void Generate(unsigned int width, unsigned int height, unsigned char* data);

	void Bind() const;
};

class Texture2DLoader : public ResourceLoader {
  public:
	virtual Resource*	CreateResource(const fs::path& path) const;
	virtual std::string GetName() const { return "Texture2DLoader"; }
};

} // namespace EngineS
