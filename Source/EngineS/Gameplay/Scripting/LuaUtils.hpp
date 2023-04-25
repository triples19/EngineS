#pragma once

#include "Core/Reflection/Variant.hpp"

extern "C" {
#include "lauxlib.h"
#include "lua.h"
#include "lualib.h"
}

namespace EngineS::LuaUtils {

inline Variant LuaToVariant(lua_State* L, int idx) {
    switch (lua_type(L, idx)) {
        case LUA_TNIL:
            return {};
        case LUA_TBOOLEAN:
            return static_cast<bool>(lua_toboolean(L, idx));
        case LUA_TNUMBER:
            if (lua_isinteger(L, idx)) {
                return static_cast<int>(lua_tointeger(L, idx));
            } else {
                return static_cast<double>(lua_tonumber(L, idx));
            }
        case LUA_TSTRING:
            return std::string(lua_tostring(L, idx));
        case LUA_TUSERDATA:
        case LUA_TLIGHTUSERDATA:
            return *reinterpret_cast<Variant*>(lua_touserdata(L, idx));
    }
    return {};
}

inline const Type* LuaTypeOf(lua_State* L, int idx) {
    switch (lua_type(L, idx)) {
        case LUA_TNIL:
            return nullptr;
        case LUA_TBOOLEAN:
            return TypeOf<bool>();
        case LUA_TNUMBER:
            if (lua_isinteger(L, idx)) {
                return TypeOf<int>();
            } else {
                return TypeOf<double>();
            }
        case LUA_TSTRING:
            return TypeOf<std::string>();
        case LUA_TUSERDATA:
            return reinterpret_cast<Variant*>(lua_touserdata(L, idx))->GetType();
    }
    return nullptr;
}

inline void LuaPushVariant(lua_State* L, const Variant& var) {
    if (!var.IsValid()) {
        lua_pushnil(L);
        return;
    }
    auto type = var.GetType();
    if (type->IsIntegral()) {
        lua_pushinteger(L, var.GetInt());
    } else if (type->IsFloatingPoint()) {
        lua_pushnumber(L, var.GetDouble());
    } else {
        new (lua_newuserdata(L, sizeof(Variant))) Variant(var);
        luaL_setmetatable(L, type->GetName().data());
    }
}

template<bool HasRet, class... Args>
inline Variant LuaCallFunc(lua_State* L, Args&&... args) {
    constexpr size_t argCount = sizeof...(Args);

    ((LuaPushVariant(L, std::forward<Args>(args))), ...);

    if (lua_pcall(L, argCount, HasRet ? 1 : 0, 0)) {
        luaL_error(L, "Error calling function: %s", lua_tostring(L, -1));
    }

    if constexpr (HasRet) {
        auto ret = LuaToVariant(L, -1);
        lua_pop(L, -1);
        return ret;
    } else {
        return {};
    }
}

} // namespace EngineS::LuaUtils