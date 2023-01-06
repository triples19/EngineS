#pragma once

#include "EngineS.hpp"

using namespace EngineS;

class TestComponent : public Component {
    ES_OBJECT
  public:
    void Update(float deltaTime) override;
};
