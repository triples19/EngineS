#include "GameObject.hpp"

namespace EngineS {

GameObject::GameObject() {
	transform = AddComponent<Transform2D>(std::make_unique<Transform2D>());
}

void GameObject::Update(float deltaTime) {
	for (auto& component : _components) {
		component.second->Update(deltaTime);
	}
}

} // namespace EngineS