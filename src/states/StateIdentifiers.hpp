#ifndef MINESWEEPER_STATEIDENTIFIERS_HPP
#define MINESWEEPER_STATEIDENTIFIERS_HPP

#include <string>
#include <optional>
#include <algorithm>
#include <cctype>

enum class StateID {
    None,
    Empty,
    MainMenu,
    DifficultyMenu,
    CustomDifficulty,
    Game,
    About
};

inline const char* toString(const StateID id) noexcept {
    switch (id) {
    case StateID::None: return "None";
    case StateID::Empty: return "Empty";
    case StateID::MainMenu: return "MainMenu";
    case StateID::DifficultyMenu: return "DifficultyMenu";
    case StateID::CustomDifficulty: return "CustomDifficulty";
    case StateID::Game: return "Game";
    case StateID::About: return "About";
    default: return "Unknown";
    }
}

inline std::optional<StateID> parseStateID(const std::string_view name) noexcept {
    auto equals = [](std::string_view a, std::string_view b) {
        return std::equal(a.begin(), a.end(), b.begin(), b.end(),
                          [](const char ca, const char cb) { return std::tolower(ca) == std::tolower(cb); });
    };

    if (equals(name, "main")) return StateID::MainMenu;
    if (equals(name, "difficulty")) return StateID::DifficultyMenu;
    if (equals(name, "custom")) return StateID::CustomDifficulty;
    if (equals(name, "game")) return StateID::Game;
    if (equals(name, "about")) return StateID::About;
    if (equals(name, "Empty")) return StateID::Empty;

    return std::nullopt;
}

#endif //MINESWEEPER_STATEIDENTIFIERS_HPP
