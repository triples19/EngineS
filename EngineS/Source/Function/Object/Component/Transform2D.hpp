#pragma once

#include "Component.hpp"
#include "Core/Math/MathHeaders.hpp"

#include <vector>

namespace EngineS {

class Transform2D : public Component {
  public:
	const auto& GetLocalPosition() const { return _position; }
	void		SetLocalPosition(const Vector2& position) { _position = position; }
	const auto& GetLocalScale() const { return _scale; }
	void		SetLocalScale(const Vector2& scale) { _scale = scale; }
	const auto& GetLocalRotation() const { return _rotation; }
	void		SetLocalRotation(float rotation) { _rotation = rotation; }

	const auto& GetPosition() const { return _position; }

	Matrix4x4 MakeModelMatrix() const;

  private:
	Vector2 _position;
	Vector2 _scale {1.0f, 1.0f};
	float	_rotation;
};

} // namespace EngineS
