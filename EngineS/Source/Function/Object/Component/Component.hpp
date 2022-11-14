#pragma once

#include "Core/Base/Object.hpp"

namespace EngineS {

class GameObject;
class Transform2D;
class Renderer;

class Component : public Object {
  public:
	virtual void Initialize(GameObject* parent);
	virtual void Update(float deltaTime) {}

  public:
	bool		 enabled {true};
	GameObject*	 gameObject {nullptr};
	Transform2D* transform {nullptr};
	Renderer*	 renderer {nullptr};
};

} // namespace EngineS
