#pragma once

#include "Function/Component.hpp"
#include "Math/Math.hpp"

namespace EngineS {

class Renderer : public Component {
    ES_OBJECT
  public:
    virtual void Render(const Matrix4x4& modelMat) {}
};

} // namespace EngineS
