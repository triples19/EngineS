#include "GameObject.hpp"

namespace EngineS {

void GameObject::Update(float deltaTime) {
	for (auto& component : _components) {
		component.second->Update(deltaTime);
	}
}

} // namespace EngineS