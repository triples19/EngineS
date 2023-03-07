#include <catch2/catch_test_macros.hpp>
#include <type_traits>

#include "Reflection/Instance.hpp"
#include "Reflection/Registration.hpp"
#include "Reflection/Utils.hpp"
#include "Reflection/Variant.hpp"

using namespace EngineS;

namespace Test_Instance {

struct A {
    ES_REFL_ENABLE
    virtual char Name() { return 'A'; }
};
struct B : A {
    ES_REFL_ENABLE
    char Name() override { return 'B'; }
};
struct C : B {
    ES_REFL_ENABLE
    char Name() override { return 'C'; }
};
struct D : C {
    ES_REFL_ENABLE
    char Name() override { return 'D'; }
};

} // namespace Test_Instance

TEST_CASE("Instance") {
    using namespace Test_Instance;

    auto typeA = Registration::Class<A>("Test_Instance::A").Get();
    auto typeB = Registration::Class<B>("Test_Instance::B").Bases<A>().Get();
    auto typeC = Registration::Class<C>("Test_Instance::C").Bases<B>().Get();
    auto typeD = Registration::Class<D>("Test_Instance::D").Bases<C>().Get();
    TypeRegistry::Instance()->ProcessBases();

    SECTION("Instance") {
        auto ptr = new C;

        Instance instance = ptr;

        REQUIRE(instance.TryConvert<A>() == ptr);
        REQUIRE(instance.TryConvert<B>() == ptr);
        REQUIRE(instance.TryConvert<D>() == nullptr);

        delete ptr;
    }

    SECTION("Variant") {
        C       c;
        Variant var = &c;
    }
}