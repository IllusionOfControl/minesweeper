#ifndef MINESWEEPER_MAINMENUSTATE_HPP
#define MINESWEEPER_MAINMENUSTATE_HPP

#include <SFML/Graphics.hpp>
#include "../MineSweeper.hpp"
#include "../DEFINITIONS.h"
#include "State.hpp"
#include "GameState.hpp"
#include "AboutState.hpp"
#include "DifficultyMenuState.hpp"
#include "../gui/Button.hpp"
#include "../gui/Background.hpp"
#include "../gui/Container.hpp"


class MainMenuState: public State {
public:
    typedef std::unique_ptr<State> Ptr;
public:
    explicit MainMenuState(GameDataRef);

    void init() override;

    void handleInput() override;
    void update() override;
    void draw() override;

private:
    GameDataRef mContext;

    sf::Sprite mBackground;
    sf::Sprite mLogo;
    Container mGuiContainer;
};


#endif //MINESWEEPER_MAINMENUSTATE_HPP
