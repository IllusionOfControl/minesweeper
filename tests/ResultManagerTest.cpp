#include <catch2/catch_test_macros.hpp>

#include "managers/ResultManager.hpp"

TEST_CASE("GameResult serialization to JSON and back preserves all fields") {
    GameResult original;
    original.playerName = "Alice";
    original.difficulty = "Medium";
    original.timeSeconds = 42;
    original.width = 16;
    original.height = 16;
    original.mines = 40;
    original.date = "2026-09-29 12:00:00";
    original.won = true;

    nlohmann::json j = original;
    const auto restored = j.get<GameResult>();

    REQUIRE(restored.playerName == "Alice");
    REQUIRE(restored.difficulty == "Medium");
    REQUIRE(restored.timeSeconds == 42);
    REQUIRE(restored.width == 16);
    REQUIRE(restored.height == 16);
    REQUIRE(restored.mines == 40);
    REQUIRE(restored.date == "2026-09-29 12:00:00");
    REQUIRE(restored.won == true);
}

TEST_CASE("serializeJson and deserializeJson handle multiple records") {
    std::vector<GameResult> results;

    GameResult r1;
    r1.playerName = "Bob";
    r1.difficulty = "Easy";
    r1.timeSeconds = 15;
    results.push_back(r1);

    GameResult r2;
    r2.playerName = "Charlie";
    r2.difficulty = "Hard";
    r2.timeSeconds = 120;
    results.push_back(r2);

    const std::string jsonStr = ResultManager::serializeJson(results);
    REQUIRE_FALSE(jsonStr.empty());

    const auto parsed = ResultManager::deserializeJson(jsonStr);
    REQUIRE(parsed.size() == 2);
    REQUIRE(parsed[0].playerName == "Bob");
    REQUIRE(parsed[0].timeSeconds == 15);
    REQUIRE(parsed[1].playerName == "Charlie");
    REQUIRE(parsed[1].timeSeconds == 120);
}

TEST_CASE("deserializeJson gracefully handles empty or invalid JSON") {
    REQUIRE(ResultManager::deserializeJson("").empty());
    REQUIRE(ResultManager::deserializeJson("not a json").empty());
    REQUIRE(ResultManager::deserializeJson("{\"key\": \"value\"}").empty()); // not an array
}
