#ifndef MINESWEEPER_SAVERESULTSTATE_HPP
#define MINESWEEPER_SAVERESULTSTATE_HPP

#include "State.hpp"
#include "gui/Background.hpp"
#include "gui/Button.hpp"
#include "gui/Container.hpp"
#include "gui/Image.hpp"
#include "gui/Input.hpp"
#include "gui/Text.hpp"

class SaveResultState : public State {
public:
    explicit SaveResultState(GameContext& context);

    void init() override;
    void handleInput() override;
    void update() override;
    void draw() override;

private:
    void save();

    Background mBackground;
    Container mGuiContainer;

    Image::Ptr mTimeLabel;
    Image::Ptr mTimeBackground;
    Text::Ptr mTimeText;

    Image::Ptr mNameLabel;
    Input::Ptr mNameInput;

    Button::Ptr mSaveButton;

    bool mSaved = false;
};

#endif // MINESWEEPER_SAVERESULTSTATE_HPP
