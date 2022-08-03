#include "Transform2D.hpp"

namespace EngineS {

Matrix4x4 Transform2D::MakeModelMatrix() const {
	auto translateMat = Translate(position.x, position.y, 0.0f);
	auto scaleMat	  = Scale(scale.x, scale.y, 1.0f);
	return scaleMat * translateMat;
}

} // namespace EngineS