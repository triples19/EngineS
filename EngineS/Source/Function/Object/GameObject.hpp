#pragma once

#include <memory>
#include <typeindex>
#include <unordered_map>
#include <vector>

#include "Components/Component.hpp"

namespace EngineS {

class GameObject {
  public:
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
	void AddComponent(std::unique_ptr<T> comp) {
		_components.insert(std::make_pair(static_cast<std::type_index>(typeid(T)), std::move(comp)));
	}

  private:
	std::unordered_multimap<std::type_index, std::unique_ptr<Component>> _components;
};

} // namespace EngineS
