#pragma once

#include <memory>

namespace EngineS {

class Program;
class Texture2D;

class Material2D {
  public:
	Material2D(std::shared_ptr<Program> program, std::shared_ptr<Texture2D> texture);

	auto GetProgram() const { return _program; }
	auto GetTexture() const { return _texture; }
	auto GetID() const { return _id; };

  private:
	static unsigned int		   _maxID;
	unsigned int			   _id;
	std::shared_ptr<Program>   _program;
	std::shared_ptr<Texture2D> _texture;
};

} // namespace EngineS
