#include <catch2/catch_test_macros.hpp>

#include "Difficulty.hpp"

TEST_CASE("Difficulty presets have standard dimensions and mine counts") {
    const auto easy = Difficulty::create(Difficulty::Preset::Easy);
    REQUIRE(easy.getWidth() == 9);
    REQUIRE(easy.getHeight() == 9);
    REQUIRE(easy.getMineCount() == 10);
    REQUIRE(easy.getTotalCells() == 81);
    REQUIRE(easy.getPreset() == Difficulty::Preset::Easy);

    const auto medium = Difficulty::create(Difficulty::Preset::Medium);
    REQUIRE(medium.getWidth() == 16);
    REQUIRE(medium.getHeight() == 16);
    REQUIRE(medium.getMineCount() == 40);
    REQUIRE(medium.getTotalCells() == 256);
    REQUIRE(medium.getPreset() == Difficulty::Preset::Medium);

    const auto hard = Difficulty::create(Difficulty::Preset::Hard);
    REQUIRE(hard.getWidth() == 32);
    REQUIRE(hard.getHeight() == 16);
    REQUIRE(hard.getMineCount() == 99);
    REQUIRE(hard.getTotalCells() == 512);
    REQUIRE(hard.getPreset() == Difficulty::Preset::Hard);
}

TEST_CASE("Difficulty custom creation enforces bounds") {
    // Valid boundary values
    REQUIRE(Difficulty::createCustom(5, 5, 1).has_value());
    REQUIRE(Difficulty::createCustom(32, 24, 767).has_value());
    REQUIRE(Difficulty::createCustom(10, 10, 20).has_value());

    // Invalid width
    REQUIRE_FALSE(Difficulty::createCustom(4, 10, 5).has_value());
    REQUIRE_FALSE(Difficulty::createCustom(33, 10, 5).has_value());

    // Invalid height
    REQUIRE_FALSE(Difficulty::createCustom(10, 4, 5).has_value());
    REQUIRE_FALSE(Difficulty::createCustom(10, 25, 5).has_value());

    // Invalid mines
    REQUIRE_FALSE(Difficulty::createCustom(10, 10, 0).has_value());
    REQUIRE_FALSE(Difficulty::createCustom(10, 10, 100).has_value()); // max is 99 (width*height - 1)
}

TEST_CASE("Difficulty equality compares width, height, and mine count") {
    const auto easy1 = Difficulty::create(Difficulty::Preset::Easy);
    const auto easy2 = Difficulty::create(Difficulty::Preset::Easy);
    const auto medium = Difficulty::create(Difficulty::Preset::Medium);

    REQUIRE(easy1 == easy2);
    REQUIRE_FALSE(easy1 == medium);
}

TEST_CASE("toString converts Difficulty::Preset to readable string") {
    REQUIRE(std::string(toString(Difficulty::Preset::Easy)) == "Easy");
    REQUIRE(std::string(toString(Difficulty::Preset::Medium)) == "Medium");
    REQUIRE(std::string(toString(Difficulty::Preset::Hard)) == "Hard");
    REQUIRE(std::string(toString(Difficulty::Preset::Custom)) == "Custom");
}
