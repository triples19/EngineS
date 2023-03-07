#include <catch2/catch_test_macros.hpp>
#include <type_traits>

#include "Reflection/ConstructorInfo.hpp"
#include "Reflection/DestructorInfo.hpp"
#include "Reflection/FieldInfo.hpp"
#include "Reflection/Instance.hpp"
#include "Reflection/MethodInfo.hpp"
#include "Reflection/Registration.hpp"
#include "Reflection/Utils.hpp"
#include "Reflection/Variant.hpp"

using namespace EngineS;

namespace Test_Constructors {

class A {
  public:
    A() : _x(-1) {}
    A(int a) : _x(a) {}
    A(int a, int b) : _x(a + b) {}

    int GetX() const { return _x; }

  private:
    int _x;
};

} // namespace Test_Constructors

TEST_CASE("Constructors") {
    using namespace Test_Constructors;
    auto typeA = Registration::Class<A>("Test_Constructors::A") //
                     .Constructor<>({})
                     .Constructor<int>({"a"})
                     .Constructor<int, int>({"a", "b"})
                     .Get();
    auto ctor1 = typeA->GetConstructor({});
    auto ctor2 = typeA->GetConstructor({TypeOf<int>()});
    auto ctor3 = typeA->GetConstructor({TypeOf<int>(), TypeOf<int>()});
    auto dtor  = typeA->GetDestructor();

    SECTION("Invoke") {
        auto a1 = ctor1->Invoke().GetValue<A*>();
        REQUIRE(a1->GetX() == -1);
        dtor->Invoke(a1);

        auto a2 = ctor2->Invoke(2).GetValue<A*>();
        REQUIRE(a2->GetX() == 2);
        dtor->Invoke(a2);

        auto a3 = ctor3->Invoke(2, 3).GetValue<A*>();
        REQUIRE(a3->GetX() == 2 + 3);
        dtor->Invoke(a3);
    }
}