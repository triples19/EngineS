#define CATCH_CONFIG_RUNNER
#include <catch2/catch_all.hpp>

int main(int argc, const char* argv[]) {
    return Catch::Session().run(argc, argv);
}