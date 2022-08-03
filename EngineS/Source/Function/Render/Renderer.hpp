#pragma once

#include "Function/Object/Component/Component.hpp"

namespace EngineS {

class Renderer : public Component {
  public:
	virtual void Render() = 0;
};

} // namespace EngineS
