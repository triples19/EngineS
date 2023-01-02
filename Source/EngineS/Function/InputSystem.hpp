#pragma once

#include "Base/Object.hpp"
#include "Function/KeyCode.hpp"

#include <functional>
#include <unordered_map>
#include <vector>

namespace EngineS {

enum class KeyAction { Press, Release };

class WindowSystem;

class InputSystem : public Object {
    ES_OBJECT
  public:
    static InputSystem* Instance();
    InputSystem() = default;

    void Initialize();
    void Update();
    bool GetKey(KeyCode key);
    bool GetKeyDown(KeyCode key);
    bool GetKeyUp(KeyCode key);

  private:
    void OnKey(int key, int scanCode, int action, int mods);

  private:
    struct KeyState {
        bool downThisFrame {false};
        bool downLastFrame {false};
    };
    std::unordered_map<KeyCode, KeyState> _keys;
};

} // namespace EngineS
