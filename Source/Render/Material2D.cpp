#include "Material2D.hpp"

namespace EngineS {

unsigned int Material2D::_maxID = 0;

Material2D::Material2D(std::shared_ptr<Program> program, std::shared_ptr<Texture2D> texture) :
	_program {program}, _texture {texture} {
	_id = ++_maxID;
}

} // namespace EngineS