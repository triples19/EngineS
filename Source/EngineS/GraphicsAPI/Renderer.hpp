#pragma once

#include "GameObject/Component.hpp"
#include "Math/Math.hpp"

namespace EngineS {

class DrawList;

class Renderer : public Component {
    ES_OBJECT
  public:
    virtual void Render(const Matrix4x4& modelMat, DrawList* drawList) {}
};

} // namespace EngineS
