#ifndef MINESWEEPER_LEADERBOARDSTATE_HPP
#define MINESWEEPER_LEADERBOARDSTATE_HPP

#include <string>
#include <vector>

#include "State.hpp"
#include "gui/Background.hpp"
#include "gui/Button.hpp"
#include "gui/Container.hpp"
#include "gui/Image.hpp"
#include "gui/Text.hpp"

class LeaderboardState : public State {
public:
    explicit LeaderboardState(GameContext& context);

    void init() override;
    void handleInput() override;
    void update() override;
    void draw() override;

private:
    void refreshRecords() const;
    void switchDifficulty(int direction);

    Background mBackground;
    Container mGuiContainer;

    Text::Ptr mFilterText;
    Text::Ptr mHeaderRowText;
    Text::Ptr mStatusMessageText;
    std::vector<Text::Ptr> mRecordRowTexts;

    Image::Ptr mFilterTextBackground;
    Image::Ptr mHeaderRowBackground;
    Image::Ptr mLeaderTableBackground;

    std::vector<std::string> mDifficultyFilters;
    std::size_t mCurrentFilterIndex = 0;
};

#endif // MINESWEEPER_LEADERBOARDSTATE_HPP