#pragma once

namespace EngineS {

class GameObject;
class Transform2D;

class Component {
  public:
	virtual void Initialize(GameObject* parent);
	virtual void Update(float deltaTime) {}

  public:
	GameObject*	 gameObject;
	Transform2D* transform;
};

} // namespace EngineS
