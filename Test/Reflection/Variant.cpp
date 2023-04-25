#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_all.hpp>
#include <type_traits>

#include "Core/Reflection/Registration.hpp"
#include "Core/Reflection/Variant.hpp"

using namespace EngineS;

struct CustomStruct {
    int   x;
    float y;

    bool operator==(const CustomStruct& rhs) const { return x == rhs.x && y == rhs.y; }
};

TEST_CASE("Variant") {
    using namespace Catch::Matchers;

    SECTION("Primitive types") {
        Variant var;

        REQUIRE_FALSE(var.IsValid());

        var = 1;
        REQUIRE(var.IsType<int>());
        REQUIRE_FALSE(var.IsType<float>());
        REQUIRE(var.GetValue<int>() == 1);

        var = 1.05f;
        REQUIRE(var.IsType<float>());
        REQUIRE_FALSE(var.IsType<double>());
        REQUIRE(var.GetValue<float>() == 1.05f);
    }

    Registration::Class<CustomStruct>("CustomStruct");

    SECTION("Custom types") {
        Variant var = CustomStruct {
            .x = 10,
            .y = 2.5f,
        };

        REQUIRE(var.IsType<CustomStruct>());
        REQUIRE_FALSE(var.IsType<int>());

        auto value = var.GetValue<CustomStruct>();
        REQUIRE(value.x == 10);
        REQUIRE(value.y == 2.5f);
    }

    SECTION("GetValue") {
        Variant var = 1.0f;
        REQUIRE(var.GetValue<float>() == 1.0f);
        var.GetValue<float>() = 5.2f;
        REQUIRE(var.GetValue<float>() == 5.2f);
    }

    SECTION("Copy construct & copy assignment") {
        Variant var1 = 10;

        Variant var2(var1);
        REQUIRE(var2.IsType<int>());
        REQUIRE(var2.GetValue<int>() == 10);

        Variant var3 = 'a';
        var2         = var3;
        REQUIRE(var2.IsType<char>());
        REQUIRE(var2.GetValue<char>() == 'a');
    }

    SECTION("Move construct & move assignment") {
        Variant var1     = 10;
        auto    address1 = &var1.GetValue<int>();

        Variant var2(std::move(var1));
        REQUIRE_FALSE(var1.IsValid()); // NOLINT
        REQUIRE(var2.IsType<int>());
        REQUIRE(var2.GetValue<int>() == 10);
        // var2 should use the same address(pointer) as var1
        REQUIRE(address1 == &var2.GetValue<int>());

        Variant var3     = 'a';
        auto    address3 = &var3.GetValue<char>();
        var2             = std::move(var3);
        REQUIRE_FALSE(var3.IsValid()); // NOLINT
        REQUIRE(var2.IsType<char>());
        REQUIRE(var2.GetValue<char>() == 'a');
        REQUIRE(address3 == &var2.GetValue<char>());
    }

    SECTION("VariantVector") {
        SECTION("Single level & same type") {
            std::vector<int> intVec {1, 2, 3};
            Variant          var = intVec;
            REQUIRE(var.IsType<VariantVector>());
            auto varVec = var.GetValue<VariantVector>();
            REQUIRE(varVec.size() == 3);
            REQUIRE(varVec[0] == 1);
            REQUIRE(varVec[1] == 2);
            REQUIRE(varVec[2] == 3);
        }

        SECTION("Single level & mutliple types") {
            Variant var = VariantVector {5, 5.0f, 'c'};
            REQUIRE(var.IsType<VariantVector>());
            auto varVec = var.GetValue<VariantVector>();
            REQUIRE(varVec.size() == 3);
            REQUIRE(varVec[0] == 5);
            REQUIRE(varVec[1] == 5.0f);
            REQUIRE(varVec[2] == 'c');
        }

        SECTION("Multiple levels") {
            Variant var = VariantVector {
                VariantVector {5.0f, 1},
                VariantVector {CustomStruct {.x = 1, .y = 1.0f}, CustomStruct {.x = 2, .y = 2.2f}}};
            REQUIRE(var.IsType<VariantVector>());
            auto varVec0 = var.GetValue<VariantVector>();
            REQUIRE(varVec0.size() == 2);

            REQUIRE(varVec0[0].IsType<VariantVector>());
            auto varVec1 = varVec0[0].GetValue<VariantVector>();
            REQUIRE(varVec1.size() == 2);
            REQUIRE(varVec1[0] == 5.0f);
            REQUIRE(varVec1[1] == 1);

            REQUIRE(varVec0[1].IsType<VariantVector>());
            auto varVec2 = varVec0[1].GetValue<VariantVector>();
            REQUIRE(varVec2.size() == 2);
            REQUIRE(varVec2[0].GetValue<CustomStruct>() == CustomStruct {.x = 1, .y = 1.0f});
            REQUIRE(varVec2[1] == CustomStruct {.x = 2, .y = 2.2f});
        }
    }

    SECTION("VariantMap") {
        SECTION("Single level & same type") {
            Variant var = std::unordered_map<hash32, int> {{32, 1}, {99, 2}};
            REQUIRE(var.IsType<VariantMap>());
            auto varMap = var.GetValue<VariantMap>();
            REQUIRE(varMap.size() == 2);
            REQUIRE(varMap.contains(32));
            REQUIRE(varMap[32] == 1);
            REQUIRE(varMap.contains(99));
            REQUIRE(varMap[99] == 2);
        }
    }
}