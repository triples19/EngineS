#pragma once

#include "Core/Base/Types.hpp"
#include "Core/Math/MathHeaders.hpp"
#include "Platform/GLCommon.hpp"

#include <array>
#include <memory>
#include <vector>

namespace EngineS {

class Program;
class Texture2D;
class Material2D;
class Transform2D;

class SpriteBatch {
  public:
	using Triangle = std::array<V2F_C4F_T2F, 3>;

	SpriteBatch(std::shared_ptr<Material2D> material);
	SpriteBatch(std::shared_ptr<Texture2D> texture, std::shared_ptr<Program> program);

	void Add(const Matrix4x4& modelMat, const Vector2& anchor, const Color4F& color);

	void Draw();

  private:
	std::shared_ptr<Texture2D> _texture;
	std::shared_ptr<Program>   _program;
	std::vector<Triangle>	   _triangles;

	GLuint _vao;
	GLuint _vbo;
};

} // namespace EngineS