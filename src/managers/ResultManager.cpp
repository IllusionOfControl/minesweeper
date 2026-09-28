#include "ResultManager.hpp"

#include <algorithm>
#include <chrono>
#include <ctime>
#include <fstream>
#include <spdlog/spdlog.h>

void to_json(nlohmann::json& j, const GameResult& r) {
    j = nlohmann::json{
        {"playerName", r.playerName},
        {"difficulty", r.difficulty},
        {"timeSeconds", r.timeSeconds},
        {"width", r.width},
        {"height", r.height},
        {"mines", r.mines},
        {"date", r.date},
        {"won", r.won}
    };
}

void from_json(const nlohmann::json& j, GameResult& r) {
    r.playerName = j.value("playerName", "Player");
    r.difficulty = j.value("difficulty", "Easy");
    r.timeSeconds = j.value("timeSeconds", 0);
    r.width = j.value("width", 9);
    r.height = j.value("height", 9);
    r.mines = j.value("mines", 10);
    r.date = j.value("date", "");
    r.won = j.value("won", true);
}

namespace ResultManager {

std::string getCurrentDateTime() {
    const auto now = std::chrono::system_clock::now();
    const auto timeT = std::chrono::system_clock::to_time_t(now);
    std::tm tm{};
#if defined(_WIN32)
    localtime_s(&tm, &timeT);
#else
    localtime_r(&timeT, &tm);
#endif
    char buf[32];
    std::strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", &tm);
    return std::string(buf);
}

std::filesystem::path getAppDataPath() {
#if defined(_WIN32)
    const char* appData = std::getenv("APPDATA");
    if (appData && *appData) {
        return std::filesystem::path(appData) / "Minesweeper";
    }
    const char* localAppData = std::getenv("LOCALAPPDATA");
    if (localAppData && *localAppData) {
        return std::filesystem::path(localAppData) / "Minesweeper";
    }
#endif
    const char* home = std::getenv("HOME");
    if (home && *home) {
        return std::filesystem::path(home) / ".minesweeper";
    }
    return std::filesystem::current_path() / "MinesweeperData";
}

std::filesystem::path getResultsFilePath() {
    return getAppDataPath() / "results.json";
}

std::string serializeJson(const std::vector<GameResult>& results) {
    const nlohmann::json j = results;
    return j.dump(4);
}

std::vector<GameResult> deserializeJson(const std::string_view json) {
    if (json.empty()) {
        return {};
    }
    try {
        const auto j = nlohmann::json::parse(json);
        if (j.is_array()) {
            return j.get<std::vector<GameResult>>();
        }
    } catch (const std::exception& e) {
        spdlog::error("ResultManager: Failed to parse JSON: {}", e.what());
    }
    return {};
}

bool saveResult(const GameResult& result) {
    const auto dir = getAppDataPath();
    std::error_code ec;
    std::filesystem::create_directories(dir, ec);
    if (ec) {
        spdlog::error("ResultManager: Failed to create directory '{}': {}", dir.string(), ec.message());
        return false;
    }

    auto results = loadResults();
    results.push_back(result);

    const auto filePath = getResultsFilePath();
    std::ofstream file(filePath, std::ios::trunc);
    if (!file.is_open()) {
        spdlog::error("ResultManager: Failed to open file for writing: {}", filePath.string());
        return false;
    }

    try {
        const nlohmann::json j = results;
        file << j.dump(4);
        spdlog::info("ResultManager: Saved result for '{}' ({}s) to {}", result.playerName, result.timeSeconds, filePath.string());
        return true;
    } catch (const std::exception& e) {
        spdlog::error("ResultManager: Failed to serialize JSON: {}", e.what());
        return false;
    }
}

std::vector<GameResult> loadResults() {
    const auto filePath = getResultsFilePath();
    std::ifstream file(filePath);
    if (!file.is_open()) {
        return {};
    }

    try {
        nlohmann::json j;
        file >> j;
        if (j.is_array()) {
            return j.get<std::vector<GameResult>>();
        }
    } catch (const std::exception& e) {
        spdlog::warn("ResultManager: Failed to read results from '{}': {}", filePath.string(), e.what());
    }
    return {};
}

std::vector<GameResult> getTopResults(const std::string_view difficulty, const std::size_t limit) {
    auto results = loadResults();
    std::vector<GameResult> filtered;
    filtered.reserve(results.size());

    for (const auto& r : results) {
        if (!r.won) {
            continue;
        }
        if (!difficulty.empty() && difficulty != "All" && r.difficulty != difficulty) {
            continue;
        }
        filtered.push_back(r);
    }

    std::sort(filtered.begin(), filtered.end(), [](const GameResult& a, const GameResult& b) {
        if (a.timeSeconds != b.timeSeconds) {
            return a.timeSeconds < b.timeSeconds;
        }
        return a.date < b.date;
    });

    if (filtered.size() > limit) {
        filtered.resize(limit);
    }
    return filtered;
}

bool clearResults() {
    const auto filePath = getResultsFilePath();
    std::error_code ec;
    return std::filesystem::remove(filePath, ec);
}

}