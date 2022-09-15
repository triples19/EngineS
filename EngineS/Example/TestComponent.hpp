#pragma once

#include "EngineS.hpp"

using namespace EngineS;

class TestComponent : public Component {
  public:
	void Update(float deltaTime) override;
};
