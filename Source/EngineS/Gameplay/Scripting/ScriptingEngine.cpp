#include "ScriptingEngine.hpp"

#include "Core/Reflection/ConstructorInfo.hpp"
#include "Core/Reflection/DestructorInfo.hpp"
#include "Core/Reflection/MethodInfo.hpp"
#include "Core/Reflection/Type.hpp"
#include "LuaUtils.hpp"

#include <algorithm>
#include <iostream>

extern "C" {
#include "lauxlib.h"
#include "lua.h"
#include "lualib.h"
}

namespace EngineS {

ScriptingEngine::ScriptingEngine() {
    _state = luaL_newstate();
    luaL_openlibs(_state);
}

ScriptingEngine::~ScriptingEngine() {
    lua_close(_state);
}

void ScriptingEngine::RunFile(const std::filesystem::path& file) {
    if (!std::filesystem::exists(file)) {
        std::cout << "file " << file << " does not exist\n";
        return;
    }
    if (luaL_dofile(_state, std::filesystem::absolute(file).string().c_str()) != LUA_OK) {
        std::cerr << lua_tostring(_state, -1) << std::endl;
    }
}

int ScriptingEngine::LuaDispatchNew(lua_State* L) {
    auto type = reinterpret_cast<Type*>(lua_touserdata(L, lua_upvalueindex(1)));

    auto                     argCount = lua_gettop(L);
    std::vector<const Type*> argTypes;
    std::vector<Variant>     args;
    for (int i = 1; i <= argCount; i++) {
        auto argType = LuaUtils::LuaTypeOf(L, i);
        if (argType == nullptr) {
            luaL_error(L, "Invalid argument type");
            return 0;
        }
        argTypes.push_back(argType);
        args.emplace_back(LuaUtils::LuaToVariant(L, i));
    }
    auto ctor = type->GetConstructor(argTypes);

    if (ctor == nullptr) {
        luaL_error(L, "Invalid constructor");
        return 0;
    }

    std::vector<Argument> actualArgs;
    actualArgs.reserve(argCount);
    std::ranges::transform(args, std::back_inserter(actualArgs), [](const Variant& var) { return Argument(var); });

    auto ud = lua_newuserdata(L, sizeof(Variant)); // Stack: [ud]
    new (ud) Variant(ctor->InvokeVariadic(actualArgs));
    lua_newtable(L);                               // Stack: [ud, tb]
    luaL_getmetatable(L, type->GetName().data());  // Stack: [ud, tb, mt]
    lua_setfield(L, -2, "__index");                // Stack: [ud, tb]
    lua_setmetatable(L, -2);                       // Stack: [ud]

    return 1;
}

int ScriptingEngine::LuaDispatchMethod(lua_State* L) {
    auto name = lua_tostring(L, lua_upvalueindex(1));
    auto type = reinterpret_cast<Type*>(lua_touserdata(L, lua_upvalueindex(2)));

    printf("[lua] %s.%s() with argCount=%d\n", type->GetName().data(), name, lua_gettop(L));

    auto instance = LuaUtils::LuaToVariant(L, 1);
    if (!instance.IsValid()) {
        luaL_error(L, "Invalid instance");
        return 0;
    }

    auto                     argCount = lua_gettop(L) - 1;
    std::vector<const Type*> argTypes;
    std::vector<Variant>     args;
    for (int i = 1; i <= argCount; i++) {
        // Skip the first argument (instance)
        auto argType = LuaUtils::LuaTypeOf(L, i + 1);
        if (argType == nullptr) {
            luaL_error(L, "Invalid argument type");
            return 0;
        }
        argTypes.push_back(argType);
        args.emplace_back(LuaUtils::LuaToVariant(L, i + 1));
    }

    auto method = type->GetMethod(name, argTypes);
    if (method == nullptr) {
        luaL_error(L, "Invalid method");
        return 0;
    }

    std::vector<Argument> actualArgs;
    actualArgs.reserve(argCount);
    std::ranges::transform(args, std::back_inserter(actualArgs), [](const Variant& var) { return Argument(var); });

    auto ret = method->InvokeVariadic(instance, actualArgs);
    if (ret.IsValid()) {
        LuaUtils::LuaPushVariant(L, ret);
        return 1;
    } else {
        return 0;
    }
}

int ScriptingEngine::LuaDispatchGC(lua_State* L) {
    auto type = reinterpret_cast<Type*>(lua_touserdata(L, lua_upvalueindex(1)));
    auto ptr  = lua_touserdata(L, 1);
    auto var  = reinterpret_cast<Variant*>(ptr);
    printf("[lua] %s.__gc\n", var->GetType()->GetName().data());

    if (var->IsValid()) {
        auto dtor = type->GetDestructor();
        dtor->Invoke(*var);
    }

    var->~Variant(); // Call destructor

    return 0;
}

void ScriptingEngine::RegisterType(const Type* type) {
    auto  L = _state;
    void* p = reinterpret_cast<void*>(const_cast<Type*>(type));

    if (luaL_newmetatable(L, type->GetName().data())) {
        // Stack: [mt]

        lua_pushvalue(L, -1);                    // Stack: [mt, mt]
        lua_setfield(L, -2, "__index");          // Stack: [mt]

        lua_pushlightuserdata(L, p);             // Stack: [mt, type]
        lua_pushcclosure(L, &LuaDispatchNew, 1); // Stack: [mt, closure]
        lua_setfield(L, -2, "New");              // Stack: [mt]

        lua_pushlightuserdata(L, p);             // Stack: [mt, type]
        lua_pushcclosure(L, &LuaDispatchGC, 1);  // Stack: [mt, closure]
        lua_setfield(L, -2, "__gc");             // Stack: [mt]

        for (auto method : type->GetMethods()) {
            lua_pushstring(L, method->GetName().data());   // Stack: [mt, name]
            lua_pushlightuserdata(L, p);                   // Stack: [mt, name, type]
            lua_pushcclosure(L, &LuaDispatchMethod, 2);    // Stack: [mt, closure]
            lua_setfield(L, -2, method->GetName().data()); // Stack: [mt]
        }

        lua_setglobal(L, type->GetName().data()); // Stack: []
    }
}

} // namespace EngineS