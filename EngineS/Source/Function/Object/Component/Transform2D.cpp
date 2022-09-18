#include "Transform2D.hpp"

namespace EngineS {

Matrix4x4 Transform2D::MakeModelMatrix() const {
	auto translateMat = Translate(_position.x, _position.y, 0.0f);
	auto rotateMat	  = RotateZ(_rotation * Math::Deg2Rad);
	auto scaleMat	  = Scale(_scale.x, _scale.y, 1.0f);
	return translateMat * rotateMat * scaleMat;
}

} // namespace EngineS