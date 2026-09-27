#ifndef MINESWEEPER_GAMESTATE_HPP
#define MINESWEEPER_GAMESTATE_HPP

#include <memory>
#include <vector>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Clock.hpp>

#include "State.hpp"
#include "Board.hpp"
#include "gui/Background.hpp"
#include "gui/Container.hpp"
#include "gui/Indicator.hpp"
#include "gui/SmileButton.hpp"

class GameState : public State {
public:
    explicit GameState(GameContext& context);

    void init() override;
    void handleInput() override;
    void update() override;
    void draw() override;

private:
    void reset();
    void initGridCells();
    void renderCells();
    void updateTimer();
    sf::Vector2i cellAt(sf::Vector2i pixel) const;

    Background mBackground;
    Container mGuiContainer;

    std::unique_ptr<Board> mBoard;
    std::vector<sf::Sprite> mGridCells;

    bool mNeedToUpdate = false;
    int mGameTime = 0;
    int mPressedCell = -1;

    sf::Clock mGameClock;

    Indicator::Ptr mMinesLeftIndicator;
    Indicator::Ptr mTimeLeftIndicator;
    SmileButton::Ptr mSmileButton;
};

#endif // MINESWEEPER_GAMESTATE_HPP
