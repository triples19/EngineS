#pragma once

#include "Component.hpp"
#include "Core/Math/MathHeaders.hpp"

namespace EngineS {

class Camera : public Component {
  public:
	void Initialize(GameObject* parent) override;
	void Update(float deltaTime) override;

	void			 ConstructProjectionMatrix();
	const Matrix4x4& GetProjectionMatrix() const;
	Matrix4x4		 GetViewMatrix() const;

  public:
	float width, height;
	float near, far;

  private:
	Matrix4x4 _projMat;
};

} // namespace EngineS
