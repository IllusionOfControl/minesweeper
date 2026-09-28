#ifndef MINESWEEPER_RESULTMANAGER_HPP
#define MINESWEEPER_RESULTMANAGER_HPP

#include <filesystem>
#include <string>
#include <string_view>
#include <vector>
#include <nlohmann/json.hpp>

struct GameResult {
    std::string playerName = "Player";
    std::string difficulty = "Easy";
    int timeSeconds = 0;
    int width = 9;
    int height = 9;
    int mines = 10;
    std::string date;
    bool won = true;
};

void to_json(nlohmann::json& j, const GameResult& r);
void from_json(const nlohmann::json& j, GameResult& r);

namespace ResultManager {
    [[nodiscard]] std::string getCurrentDateTime();
    [[nodiscard]] std::filesystem::path getAppDataPath();
    [[nodiscard]] std::filesystem::path getResultsFilePath();

    [[nodiscard]] std::string serializeJson(const std::vector<GameResult>& results);
    [[nodiscard]] std::vector<GameResult> deserializeJson(std::string_view json);

    bool saveResult(const GameResult& result);
    [[nodiscard]] std::vector<GameResult> loadResults();
    [[nodiscard]] std::vector<GameResult> getTopResults(std::string_view difficulty = "", std::size_t limit = 10);
    bool clearResults();
}

#endif // MINESWEEPER_RESULTMANAGER_HPP