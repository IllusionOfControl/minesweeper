#ifndef MINESWEEPER_MAINMENUSTATE_H
#define MINESWEEPER_MAINMENUSTATE_H

#include <SFML/Graphics.hpp>
#include "../MineSweeper.h"
#include "../DEFINITIONS.h"
#include "State.h"
#include "GameState.h"
#include "AboutState.h"
#include "DifficultyMenuState.h"
#include "LeaderboardState.h"
#include "../gui/Container.hpp"


class MainMenuState: public State {
public:
    explicit MainMenuState(GameDataRef);

    void Init() override;

    void HandleInput() override;
    void Update() override;
    void Draw() override;

private:
    GameDataRef mGameData;

    sf::Sprite mBackground;
    sf::Sprite mLogo;
    Container mGuiContainer;
};


#endif //MINESWEEPER_MAINMENUSTATE_H
