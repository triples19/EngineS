#pragma once

#include <memory>
#include <type_traits>
#include <typeindex>
#include <unordered_map>
#include <vector>

#include "Component/Component.hpp"
#include "Component/Transform2D.hpp"
#include "Function/Render/Renderer.hpp"

namespace EngineS {

class GameObject {
  public:
	GameObject();

	virtual void Update(float deltaTime);

	template<class T>
	T* GetComponent() {
		auto iter = _components.find(static_cast<std::type_index>(typeid(T)));
		if (iter == _components.end())
			return nullptr;
		return static_cast<T*>(iter->second.get());
	}

	template<class T>
	std::vector<T*> GetComponents() {
		auto			range = _components.equal_range(static_cast<std::type_index>(typeid(T)));
		std::vector<T*> comps;
		comps.reserve(std::distance(range.first, range.second));
		for (auto iter = range.first; iter != range.second; ++iter) {
			comps.push_back(static_cast<T*>(iter->second.get()));
		}
		return comps;
	}

	template<class T>
	T* AddComponent(std::unique_ptr<T> comp) {
		comp->Initialize(this);
		auto inserted = _components.insert(std::make_pair(static_cast<std::type_index>(typeid(T)), std::move(comp)));
		auto pointer  = static_cast<T*>(inserted->second.get());
		SetPropertyIfNeeded(pointer);
		return static_cast<T*>(pointer);
	}

  private:
	template<class T>
	void SetPropertyIfNeeded(T* val) {
		if constexpr (std::is_base_of_v<Renderer, T>) {
			renderer = val;
		}
	}

  public:
	Transform2D* transform;
	Renderer*	 renderer;

  private:
	std::unordered_multimap<std::type_index, std::unique_ptr<Component>> _components;
};

} // namespace EngineS
