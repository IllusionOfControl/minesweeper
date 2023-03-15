#ifndef MINESWEEPER_MAINMENUSTATE_HPP
#define MINESWEEPER_MAINMENUSTATE_HPP

#include <SFML/Graphics.hpp>
#include "../MineSweeper.hpp"
#include "../DEFINITIONS.h"
#include "State.hpp"
#include "GameState.hpp"
#include "AboutState.hpp"
#include "DifficultyMenuState.hpp"
#include "LeaderboardState.hpp"
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


#endif //MINESWEEPER_MAINMENUSTATE_HPP
