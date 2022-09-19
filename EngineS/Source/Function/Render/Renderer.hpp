#pragma once

#include "Core/Math/MathHeaders.hpp"
#include "Function/Object/Component/Component.hpp"

namespace EngineS {

class Renderer : public Component {
  public:
	virtual void Render(const Matrix4x4& modelMat) = 0;
};

} // namespace EngineS
