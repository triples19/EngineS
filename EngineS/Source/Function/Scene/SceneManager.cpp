#include "SceneManager.hpp"

#include <cassert>

namespace EngineS {

static SceneManager* s_SharedInstance;

SceneManager* SceneManager::Instance() {
	if (!s_SharedInstance) {
		s_SharedInstance = new (std::nothrow) SceneManager;
		assert(s_SharedInstance != nullptr);
	}
	return s_SharedInstance;
}

void SceneManager::Initialize() {}

} // namespace EngineS