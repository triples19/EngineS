#include <catch2/catch_tostring.hpp>

#include <Core/Container/String.hpp>

namespace Catch {
template<>
struct StringMaker<EngineS::String> {
    static std::string convert(const EngineS::String& val) { return "\"" + val.ToStdString() + "\""; }
};
} // namespace Catch