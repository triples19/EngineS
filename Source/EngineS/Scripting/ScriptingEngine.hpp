#pragma once

#include <filesystem>

struct lua_State;

namespace EngineS {

class Type;
class Variant;

class ScriptingEngine {
  public:
    ScriptingEngine();
    ~ScriptingEngine();

    void RunFile(const std::filesystem::path& file);

    template<bool HasRet, class... Args>
    Variant CallGlobalFunc(const std::string& name, Args&&... args);

    void RegisterType(const Type* type);

  private:
    static int LuaDispatchNew(lua_State* L);
    static int LuaDispatchMethod(lua_State* L);
    static int LuaDispatchGC(lua_State* L);

  private:
    lua_State* _state;
};

} // namespace EngineS

#include "Scripting/LuaUtils.hpp"

namespace EngineS {
template<bool HasRet, class... Args>
Variant ScriptingEngine::CallGlobalFunc(const std::string& name, Args&&... args) {
    auto L = _state;
    lua_getglobal(L, name.c_str());
    return LuaUtils::LuaCallFunc<HasRet, Args...>(L, std::forward<Args>(args)...);
}
} // namespace EngineS