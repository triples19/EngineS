#pragma once

#include "Core/Math/Math.hpp"
#include "Gameplay/GameObject/Component.hpp"

namespace EngineS {

class DrawList;

class Renderer : public Component {
    ES_OBJECT
  public:
    virtual void Render(const Matrix4x4& modelMat, DrawList* drawList) {}
};

} // namespace EngineS
