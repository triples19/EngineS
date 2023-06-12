#include <catch2/catch_test_macros.hpp>
#include <type_traits>

#include "Core/Reflection/FieldInfo.hpp"
#include "Core/Reflection/Instance.hpp"
#include "Core/Reflection/MethodInfo.hpp"
#include "Core/Reflection/Registration.hpp"
#include "Core/Reflection/Utils.hpp"
#include "Core/Reflection/Variant.hpp"

using namespace EngineS;

namespace Test_Methods {

struct A {
    int          foo() { return 1; }
    int          foo(int i) { return 1 + i; }
    void         bar(int& x) const { x++; }
    static float s(float x, float y) { return x + y; }
};

} // namespace Test_Methods

TEST_CASE("Methods") {
    using namespace Test_Methods;
    auto type =                                   //
        Registration::Class<A>("Test_Methods::A") //
            .Method("foo", static_cast<int (A::*)()>(&A::foo), {})
            .Method("foo", static_cast<int (A::*)(int)>(&A::foo), {"i"})
            .Method("bar", static_cast<void (A::*)(int&) const>(&A::bar), {"x"})
            .Method("s", static_cast<float (*)(float, float)>(&A::s), {"x", "y"})
            .Get();

    auto foo1 = type->GetMethod("foo", {});
    auto foo2 = type->GetMethod("foo", {TypeOf<int>()});
    auto bar  = type->GetMethod("bar", {TypeOf<int&>()});
    auto s    = type->GetMethod("s", {TypeOf<float>(), TypeOf<float>()});

    SECTION("Finding") {
        REQUIRE(foo1);
        REQUIRE(foo2);
        REQUIRE(bar);
        REQUIRE(s);
    }

    SECTION("Info") {
        REQUIRE(foo1->GetName() == "foo");
        REQUIRE_FALSE(foo1->IsStatic());
        REQUIRE(foo1->GetReturnType() == TypeOf<int>());
        REQUIRE(foo1->GetParameterCount() == 0);
        REQUIRE(foo1->GetParameterInfos().empty());

        REQUIRE(foo2->GetParameterCount() == 1);
        REQUIRE(foo2->GetParameterInfos()[0].GetType() == TypeOf<int>());
        REQUIRE(foo2->GetParameterInfos()[0].GetName() == "i");

        REQUIRE(s->IsStatic());
        REQUIRE(s->GetParameterCount() == 2);
        REQUIRE(s->GetParameterInfos()[0].GetType() == TypeOf<float>());
        REQUIRE(s->GetParameterInfos()[0].GetName() == "x");
        REQUIRE(s->GetParameterInfos()[1].GetType() == TypeOf<float>());
        REQUIRE(s->GetParameterInfos()[1].GetName() == "y");
    }

    SECTION("Invoke") {
        A a;
        REQUIRE(foo1->Invoke(a) == 1);
        REQUIRE(foo2->Invoke(a, 2) == 3);

        REQUIRE(s->Invoke({}, 1.5f, 3.0f) == 1.5f + 3.0f);
    }

    SECTION("Reference argument") {
        A   a;
        int i = 0;
        bar->Invoke(a, i);
        REQUIRE(i == 1);
    }
}