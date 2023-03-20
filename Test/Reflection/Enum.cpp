#include <catch2/catch_test_macros.hpp>
#include <type_traits>

#include "Reflection/EnumInfo.hpp"
#include "Reflection/Registration.hpp"

using namespace EngineS;

enum class E : char {
    E0,
    E1 = '1',
    E2,
    E3 = 'a',
};

TEST_CASE("Enum") {
    Registration::Enum<E>("E") //
        .Value("E0", E::E0)
        .Value("E1", E::E1)
        .Value("E2", E::E2)
        .Value("E3", E::E3);
    SECTION("") {
        auto e = TypeRegistry::Instance()->GetEnum("E");
        REQUIRE(e->GetName() == "E");
    }
}