#pragma once

#include "Component.hpp"
#include "Core/Math/MathHeaders.hpp"

#include <vector>

namespace EngineS {

class Transform2D : public Component {
  public:
	Vector2 position;
	Vector2 scale {1.0f, 1.0f};
	float	rotation;

	Matrix4x4 MakeModelMatrix() const;
};

} // namespace EngineS
