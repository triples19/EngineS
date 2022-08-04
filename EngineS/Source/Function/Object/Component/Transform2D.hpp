#pragma once

#include "Component.hpp"
#include "Core/Math/MathHeaders.hpp"

namespace EngineS {

class Transform2D : public Component {
  public:
	Vector2 position {0.0f, 0.0f};
	Vector2 scale {1.0f, 1.0f};
	float	rotation {0.0f};

	Matrix4x4 MakeModelMatrix() const;
};

} // namespace EngineS
