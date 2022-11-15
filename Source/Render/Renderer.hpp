#pragma once

#include "Function/Component.hpp"
#include "Math/MathHeaders.hpp"

namespace EngineS {

class Renderer : public Component {
  public:
    virtual void Render(const Matrix4x4& modelMat) = 0;
};

} // namespace EngineS
