#ifndef MINESWEEPER_DIFFICULTYMENUSTATE_H
#define MINESWEEPER_DIFFICULTYMENUSTATE_H

#include <SFML/Graphics.hpp>
#include "../MineSweeper.h"
#include "../DEFINITIONS.h"
#include "State.h"
#include "GameState.h"
#include "AboutState.h"
#include "CustomDifficultyState.h"


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
