#ifndef MINESWEEPER_GAMECONTEXT_HPP
#define MINESWEEPER_GAMECONTEXT_HPP

#include <optional>
#include <SFML/Graphics/RenderWindow.hpp>

#include "Difficulty.hpp"
#include "managers/AssetManager.hpp"
#include "managers/StateManager.hpp"
#include "managers/ResultManager.hpp"

struct GameContext {
    sf::RenderWindow& window;
    AssetManager& assets;
    StateManager& states;

    Difficulty& difficulty;
    std::optional<GameResult> lastResult;

    GameContext(sf::RenderWindow& windowRef,
                AssetManager& assetsRef,
                StateManager& statesRef,
                Difficulty& difficultyRef) noexcept
        : window(windowRef)
        , assets(assetsRef)
        , states(statesRef)
        , difficulty(difficultyRef) {}

    GameContext(const GameContext&) = delete;
    GameContext& operator=(const GameContext&) = delete;
    GameContext(GameContext&&) = delete;
    GameContext& operator=(GameContext&&) = delete;
};

#endif // MINESWEEPER_GAMECONTEXT_HPP