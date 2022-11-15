#include "SceneManager.hpp"
#include "Base/Macros.hpp"

namespace EngineS {

static SceneManager* s_SharedInstance;

SceneManager* SceneManager::Instance() {
	if (!s_SharedInstance) {
		s_SharedInstance = new (std::nothrow) SceneManager;
		ES_ASSERT_NOMSG(s_SharedInstance != nullptr);
	}
	return s_SharedInstance;
}

void SceneManager::Initialize() {}

} // namespace EngineS