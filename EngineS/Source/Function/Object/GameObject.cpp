#include "GameObject.hpp"

namespace EngineS {

void GameObject::Update(float deltaTime) {
	for (auto& pair : _components) {
		auto& component = pair.second;
		if (component->enabled) {
			component->Update(deltaTime);
		}
	}
}

} // namespace EngineS