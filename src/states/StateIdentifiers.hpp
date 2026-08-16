#ifndef MINESWEEPER_STATEIDENTIFIERS_HPP
#define MINESWEEPER_STATEIDENTIFIERS_HPP

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
    }
    return "Unknown";
}

#endif //MINESWEEPER_STATEIDENTIFIERS_HPP