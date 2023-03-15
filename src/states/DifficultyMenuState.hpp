#ifndef MINESWEEPER_DIFFICULTYMENUSTATE_HPP
#define MINESWEEPER_DIFFICULTYMENUSTATE_HPP

#include <SFML/Graphics.hpp>
#include "../MineSweeper.hpp"
#include "../DEFINITIONS.h"
#include "State.hpp"
#include "GameState.hpp"
#include "AboutState.hpp"
#include "CustomDifficultyState.hpp"


class DifficultyMenuState: public State  {
public:
    explicit DifficultyMenuState(GameDataRef data);

    void Init() override;

    void HandleInput() override;
    void Update() override;
    void Draw() override;

private:
    GameDataRef mGameData;

    sf::Sprite mBackground;
    Container mGuiContainer;
};

#endif
