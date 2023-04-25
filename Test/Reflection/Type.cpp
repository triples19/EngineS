#include <catch2/catch_test_macros.hpp>
#include <type_traits>

#include "Core/Reflection/Registration.hpp"
#include "Core/Reflection/Variant.hpp"

using namespace EngineS;

namespace Test_Type {

struct A {};
struct B : A {};

struct C {};
struct D : C {};

struct E : B, D {};

} // namespace Test_Type

TEST_CASE("Type") {
    using namespace Test_Type;

    Registration::Class<A>("Test_Type::A");
    Registration::Class<B>("Test_Type::B").Bases<A>();
    Registration::Class<C>("Test_Type::C");
    Registration::Class<D>("Test_Type::D").Bases<C>();
    Registration::Class<E>("Test_Type::E").Bases<B, D>();
    auto typeA = TypeOf<A>();
    auto typeE = TypeOf<E>();

    SECTION("Basic info") {
        REQUIRE(typeE->GetName() == "Test_Type::E");

        REQUIRE(typeE->Is<E>());
        REQUIRE(typeE->Is(TypeOf<E>()));
        REQUIRE(typeE->Is("Test_Type::E"));
    }

    // SECTION("Bases") {
    //     REQUIRE(typeA->IsBaseOf<E>());
    //     REQUIRE(typeA->IsBaseOf("Test_Type::E"));
    //     REQUIRE(typeA->IsBaseOf(typeE));

    //     REQUIRE(typeE->DerivedFrom<A>());
    //     REQUIRE(typeE->DerivedFrom("Test_Type::A"));
    //     REQUIRE(typeE->DerivedFrom(typeA));

    //     auto baseList = typeE->GetBaseClasses();
    // }
}