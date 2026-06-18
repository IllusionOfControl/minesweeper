#include "WidgetFactory.hpp"
#include "../DEFINITIONS.h"
#include "../states/MainMenuState.hpp"

namespace widgets {

void setupBackground(sf::Sprite &sprite, const GameDataRef &context) {
    auto &texture = context->assets.getTexture("background");
    texture.setRepeated(true);

    auto windowSize = context->window.getSize();
    sprite.setTexture(texture);
    sprite.setTextureRect({0, 0, (int) windowSize.x, (int) windowSize.y});
}

std::shared_ptr<Button> makeMainMenuButton(const GameDataRef &context) {
    auto button = std::make_shared<Button>();
    button->setTexture(context->assets.getTexture("state_buttons"));
    button->setNormalTextureRect({0, 0, SQUARE_SIZE, SQUARE_SIZE});
    button->setSelectedTextureRect({SQUARE_SIZE * 1, 0, SQUARE_SIZE, SQUARE_SIZE});
    button->setPosition(0, 0);
    button->setCallback([context]() {
        context->manager.addState(StateRef(new MainMenuState(context)), true);
    });
    return button;
}

std::shared_ptr<Button> makeExitButton(const GameDataRef &context, int widthInSquares) {
    auto button = std::make_shared<Button>();
    button->setTexture(context->assets.getTexture("state_buttons"));
    button->setNormalTextureRect({SQUARE_SIZE * 2, 0, SQUARE_SIZE, SQUARE_SIZE});
    button->setSelectedTextureRect({SQUARE_SIZE * 3, 0, SQUARE_SIZE, SQUARE_SIZE});
    button->setPosition((float) (widthInSquares + GAME_BORDER_RIGHT) * SQUARE_SIZE, 0);
    button->setCallback([context]() {
        context->window.close();
    });
    return button;
}

}
