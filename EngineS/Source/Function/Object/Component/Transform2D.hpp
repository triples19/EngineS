#pragma once

#include "Component.hpp"
#include "Core/Math/MathHeaders.hpp"

namespace EngineS {

class Transform2D : public Component {
  public:
	Vector2 position;
	Vector2 scale;
	float	rotation;

	Matrix4x4 MakeModelMatrix() const;
};

} // namespace EngineS
