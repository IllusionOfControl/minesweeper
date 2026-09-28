#include <catch2/catch_test_macros.hpp>

#include "states/StateIdentifiers.hpp"

TEST_CASE("parseStateID parses state names case-insensitively") {
    REQUIRE(parseStateID("main") == StateID::MainMenu);
    REQUIRE(parseStateID("MAIN") == StateID::MainMenu);
    REQUIRE(parseStateID("difficulty") == StateID::DifficultyMenu);
    REQUIRE(parseStateID("DIFFICULTY") == StateID::DifficultyMenu);
    REQUIRE(parseStateID("custom") == StateID::CustomDifficulty);
    REQUIRE(parseStateID("game") == StateID::Game);
    REQUIRE(parseStateID("Game") == StateID::Game);
    REQUIRE(parseStateID("about") == StateID::About);
    REQUIRE(parseStateID("save") == StateID::SaveResult);
    REQUIRE(parseStateID("saveresult") == StateID::SaveResult);
    REQUIRE(parseStateID("leaderboard") == StateID::Leaderboard);
    REQUIRE(parseStateID("empty") == StateID::Empty);

    REQUIRE_FALSE(parseStateID("unknown").has_value());
    REQUIRE_FALSE(parseStateID("").has_value());
}

TEST_CASE("toString converts StateID to matching name") {
    REQUIRE(std::string(toString(StateID::MainMenu)) == "MainMenu");
    REQUIRE(std::string(toString(StateID::DifficultyMenu)) == "DifficultyMenu");
    REQUIRE(std::string(toString(StateID::CustomDifficulty)) == "CustomDifficulty");
    REQUIRE(std::string(toString(StateID::Game)) == "Game");
    REQUIRE(std::string(toString(StateID::About)) == "About");
    REQUIRE(std::string(toString(StateID::SaveResult)) == "SaveResult");
    REQUIRE(std::string(toString(StateID::Leaderboard)) == "Leaderboard");
    REQUIRE(std::string(toString(StateID::Empty)) == "Empty");
    REQUIRE(std::string(toString(StateID::None)) == "None");
}
