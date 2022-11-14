#pragma once

#include "Component.hpp"
#include "Core/Math/MathHeaders.hpp"

#include <functional>
#include <unordered_set>

namespace EngineS {

class GameObject;

class Transform2D : public Component {
  public:
	Vector2 position;
	Vector2 scale {1.0f, 1.0f};
	float	rotation;

	Matrix4x4 MakeModelMatrix() const;

	using VisitFunc = std::function<void(GameObject*, const Matrix4x4&)>;
	void Visit(const Matrix4x4& parentModelMat, VisitFunc func);

	Transform2D* GetParent() { return _parent; }
	void		 SetParent(Transform2D* parent);
	void		 AddChild(Transform2D* child);
	void		 RemoveChild(Transform2D* child);
	void		 RemoveFromParent();
	auto&		 GetChildren() { return _children; }

  private:
	std::unordered_set<Transform2D*> _children;
	Transform2D*					 _parent;
};

} // namespace EngineS
