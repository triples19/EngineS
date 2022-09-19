#include "Transform2D.hpp"

namespace EngineS {

Matrix4x4 Transform2D::MakeModelMatrix() const {
	auto translateMat = Translate(position.x, position.y, 0.0f);
	auto rotateMat	  = RotateZ(rotation * Math::Deg2Rad);
	auto scaleMat	  = Scale(scale.x, scale.y, 1.0f);
	return translateMat * rotateMat * scaleMat;
}

} // namespace EngineS