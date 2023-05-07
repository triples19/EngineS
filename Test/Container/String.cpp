#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators_all.hpp>
#include <catch2/matchers/catch_matchers_all.hpp>
#include <type_traits>

#include <Core/Container/String.hpp>

#include "../Common.hpp"

TEST_CASE("String") {
    using namespace EngineS;
    using namespace Catch::Generators;

    SECTION("Constructors") {
        // Empty string: ""
        // Short string: "Hello"
        // Long string: "Hello World C++ Game Engine!"
        auto str = GENERATE(as<std::string> {}, "", "Hello", "Hello World C++ Game Engine!");

        String s2(str.c_str());
        REQUIRE(s2.Length() == str.size());
        REQUIRE(s2.Empty() == str.empty());
        REQUIRE_THAT(s2.GetBuffer(), Catch::Matchers::Equals(str));

        auto   randLen = GENERATE_REF(take(1, random(0, (int)str.size())));
        String s3(str.c_str(), randLen);
        REQUIRE(s3.Length() == randLen);
        REQUIRE(s3.Empty() == (randLen == 0));
        REQUIRE_THAT(s3.GetBuffer(), Catch::Matchers::Equals(str.substr(0, randLen)));

        String s4(s2);
        REQUIRE(s4.Length() == str.size());
        REQUIRE(s4.Empty() == str.empty());
        REQUIRE_THAT(s4.GetBuffer(), Catch::Matchers::Equals(str));

        String s5(std::move(s2));
        REQUIRE(s5.Length() == str.size());
        REQUIRE(s5.Empty() == str.empty());
        REQUIRE_THAT(s4.GetBuffer(), Catch::Matchers::Equals(str));
    }

    SECTION("Assignment") {
        String s1;
        s1 = "Hello";
        REQUIRE_THAT(s1.GetBuffer(), Catch::Matchers::Equals("Hello"));

        String s2;
        s2 = s1;
        REQUIRE_THAT(s2.GetBuffer(), Catch::Matchers::Equals("Hello"));

        String s3;
        s3 = std::move(s2);
        REQUIRE_THAT(s3.GetBuffer(), Catch::Matchers::Equals("Hello"));
    }

    SECTION("Comparison") {
        String s1("Hello");
        String s2("Hello");
        REQUIRE(s1 == s2);

        String s3("Hellz");
        REQUIRE(s1 != s3);
        REQUIRE(s1 < s3);
        REQUIRE(s1 <= s3);

        String s4("Hella");
        REQUIRE(s1 != s4);
        REQUIRE(s1 > s4);
        REQUIRE(s1 >= s4);

        REQUIRE(s1 == "Hello");
        REQUIRE(s1 != "");
        REQUIRE(s1 > "Hella");
        REQUIRE(s1 < "Hellz");
    }

    SECTION("Append") {
        String s1("Hello");
        s1.Append('c');
    }

    SECTION("Find") {
        String s1("Hello");
        REQUIRE(s1.Find('H') == 0);
        REQUIRE(s1.Find('H', 1) == String::NPos);
        REQUIRE(s1.Find('h') == String::NPos);
        REQUIRE(s1.Find('l') == 2);
        REQUIRE(s1.Find('l', 3) == 3);
        REQUIRE(s1.Find("lo") == 3);
        REQUIRE(s1.Find("loo") == String::NPos);
        REQUIRE(s1.Find("") == String::NPos);
        REQUIRE(s1.Find("Hello1") == String::NPos);

        String s2("lloll");
        REQUIRE(s2.Find("ll") == 0);
        REQUIRE(s2.Find("ll", 1) == 3);
        REQUIRE(s2.FindLast('l') == 4);
        REQUIRE(s2.FindLast('l', 1) == 1);
        REQUIRE(s2.FindLast("ll") == 3);
        REQUIRE(s2.FindLast("ll", 2) == 0);
    }

    SECTION("StartsWith / EndsWith") {
        String s1 = "EngineS";
        REQUIRE_FALSE(s1.StartsWith(""));
        REQUIRE(s1.StartsWith("Eng"));
        REQUIRE(s1.StartsWith("EngineS"));
        REQUIRE_FALSE(s1.StartsWith("Engh"));

        REQUIRE_FALSE(s1.EndsWith(""));
        REQUIRE(s1.EndsWith("neS"));
        REQUIRE(s1.EndsWith("EngineS"));
        REQUIRE_FALSE(s1.EndsWith("nes"));
    }

    SECTION("ToUpper / ToLower") {
        String s1("eNg iNEs");
        REQUIRE(s1.ToUpper() == "ENG INES");
        REQUIRE(s1.ToLower() == "eng ines");
    }

    SECTION("Trimmed") {
        REQUIRE(String("  Engi ne S   ").Trimmed() == "Engi ne S");
        REQUIRE(String("Engi ne S").Trimmed() == "Engi ne S");
    }

    SECTION("Substring") {
        String s1("EngineS");
        REQUIRE(s1.Substring(0) == "EngineS");
        REQUIRE(s1.Substring(7) == "");
        REQUIRE(s1.Substring(3) == "ineS");
        REQUIRE(s1.Substring(0, 3) == "Eng");
        REQUIRE(s1.Substring(0, 10) == "EngineS");
        REQUIRE(s1.Substring(6, 1) == "S");
    }

    SECTION("Replace") {
        REQUIRE(String("Say Yes!").Replace(4, 3, "No") == "Say No!");
        REQUIRE(String("Say Yes!").Replace(4, 3, "Hello") == "Say Hello!");
        REQUIRE(String("Say Yes!").Replace(4, 4, "Thanks") == "Say Thanks");

        REQUIRE(String("Hello World").Replace('l', 'L') == "HeLLo WorLd");
        REQUIRE(String("Hello World").Replace("ll", "ab") == "Heabo World");
        REQUIRE(String("HellolloeH").Replace("ll", "abcd") == "HeabcdoabcdoeH");
        REQUIRE(String("HellolloeH").Replace("ll", "") == "HeooeH");
    }

    SECTION("Insert") {
        REQUIRE(String("EngineS").Insert(0, 'E') == "EEngineS");
        REQUIRE(String("EngineS").Insert(3, 'E') == "EngEineS");
        REQUIRE(String("EngineS").Insert(9, 'E') == "EngineS  E");

        REQUIRE(String("EngineS").Insert(0, "AB") == "ABEngineS");
        REQUIRE(String("EngineS").Insert(3, "CD") == "EngCDineS");
        REQUIRE(String("EngineS").Insert(9, "ES") == "EngineS  ES");
    }

    SECTION("Split") {
        REQUIRE_THAT(
            String("Alpha,Beta,Gamma").Split(','),
            Catch::Matchers::Equals(std::vector<String> {"Alpha", "Beta", "Gamma"})
        );
        REQUIRE_THAT(
            String(",Alpha,Beta,,Gamma,").Split(','),
            Catch::Matchers::Equals(std::vector<String> {"Alpha", "Beta", "Gamma"})
        );
    }
}
