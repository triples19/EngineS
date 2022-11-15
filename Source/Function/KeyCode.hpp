#pragma once
#include <cstdint>

enum class KeyCode : int32_t {
#define KEY_CODE(name, code) name = code,
#include "KeyCode.def"
#undef KEY_CODE
};

constexpr const char* KeyCodeToString(KeyCode keyCode) noexcept {
    switch (keyCode) {
#define KEY_CODE(name, code) \
    case KeyCode::name:      \
        return #name;
#include "KeyCode.def"
#undef KEY_CODE
    }
    return "Unknown";
}