#include <catch2/catch_test_macros.hpp>
#include <type_traits>

#include "Reflection/FieldInfo.hpp"
#include "Reflection/Instance.hpp"
#include "Reflection/Registration.hpp"
#include "Reflection/Utils.hpp"
#include "Reflection/Variant.hpp"

using namespace EngineS;

namespace Test_Fields {

struct A {
    int        i;
    float      f;
    A*         p;
    static int s;
};

int A::s = 6;

} // namespace Test_Fields

TEST_CASE("Fields") {
    using namespace Test_Fields;
    auto typeA =                                 //
        Registration::Class<A>("Test_Fields::A") //
            .Field("i", &A::i)
            .Field("f", &A::f)
            .Field("p", &A::p)
            .Field("s", &A::s)
            .Get();
    auto fieldI = typeA->GetField("i");
    auto fieldF = typeA->GetField("f");
    auto fieldP = typeA->GetField("p");
    auto fieldS = typeA->GetField("s");

    SECTION("Info") {
        REQUIRE(fieldI->GetName() == "i");
        REQUIRE(fieldI->GetType() == TypeOf<int>());
        REQUIRE_FALSE(fieldI->IsStatic());

        REQUIRE(fieldS->IsStatic());
    }

    SECTION("Get/Set") {
        A t;
        A a {.i = 10, .f = 1.5f, .p = &t};
        REQUIRE(fieldI->GetValue<int>(a) == 10);
        REQUIRE(fieldF->GetValue<float>(a) == 1.5f);
        REQUIRE(fieldP->GetValue<A*>(a) == &t);
        REQUIRE(fieldS->GetValue<int>({}) == 6);

        fieldI->SetValue(a, 20);
        REQUIRE(fieldI->GetValue<int>(a) == 20);
        fieldF->SetValue(a, 5.5f);
        REQUIRE(fieldF->GetValue<float>(a) == 5.5f);
        fieldP->SetValue(a, static_cast<A*>(nullptr));
        REQUIRE(fieldP->GetValue<A*>(a) == nullptr);
        fieldS->SetValue({}, 12);
        REQUIRE(fieldS->GetValue<int>({}) == 12);
    }
}