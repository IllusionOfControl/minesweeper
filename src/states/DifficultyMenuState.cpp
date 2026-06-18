#include "DifficultyMenuState.hpp"
#include "../gui/Button.hpp"
#include "../gui/WidgetFactory.hpp"
#include "../WindowUtils.hpp"

DifficultyMenuState::DifficultyMenuState(GameDataRef context)
        : mContext(context)
        , mGuiContainer() {

}

void DifficultyMenuState::init() {
    resizeWindow(mContext->window,
                 (WIDTH + GAME_BORDER_RIGHT + GAME_BORDER_LEFT) * SQUARE_SIZE,
                 (HEIGHT + GAME_BORDER_TOP + GAME_BORDER_BOTTOM) * SQUARE_SIZE);
    widgets::setupBackground(mBackground, mContext);

    auto mainMenuButton = widgets::makeMainMenuButton(mContext);
    auto exitButton = widgets::makeExitButton(mContext, WIDTH);

    auto easyModeButton = std::make_shared<Button>();
    easyModeButton->setTexture(mContext->assets.getTexture("difficultMenuButtons"));
    easyModeButton->setNormalTextureRect({0, 0, SQUARE_SIZE * 5, SQUARE_SIZE});
    easyModeButton->setSelectedTextureRect({SQUARE_SIZE * 5, 0, SQUARE_SIZE * 5, SQUARE_SIZE});
    easyModeButton->setPosition(GAME_BORDER_RIGHT * SQUARE_SIZE, (GAME_BORDER_TOP - 2) * SQUARE_SIZE);
    easyModeButton->setCallback([this]() {
        mContext->difficulty = DIFFICULTY_EASY;
        mContext->manager.addState(StateRef(new GameState(mContext)), true);
    });


    auto normalModeButton = std::make_shared<Button>();
    normalModeButton->setTexture(mContext->assets.getTexture("difficultMenuButtons"));
    normalModeButton->setNormalTextureRect({SQUARE_SIZE * 0, SQUARE_SIZE * 1, SQUARE_SIZE * 5, SQUARE_SIZE});
    normalModeButton->setSelectedTextureRect({SQUARE_SIZE * 5, SQUARE_SIZE * 1, SQUARE_SIZE * 5, SQUARE_SIZE});
    normalModeButton->setPosition(GAME_BORDER_RIGHT * SQUARE_SIZE, GAME_BORDER_TOP * SQUARE_SIZE);
    normalModeButton->setCallback([this]() {
        mContext->difficulty = DIFFICULTY_MEDIUM;
        mContext->manager.addState(StateRef(new GameState(mContext)), true);
    });

    auto hardModeButton = std::make_shared<Button>();
    hardModeButton->setTexture(mContext->assets.getTexture("difficultMenuButtons"));
    hardModeButton->setNormalTextureRect({SQUARE_SIZE * 0, SQUARE_SIZE * 2, SQUARE_SIZE * 5, SQUARE_SIZE});
    hardModeButton->setSelectedTextureRect({SQUARE_SIZE * 5, SQUARE_SIZE * 2, SQUARE_SIZE * 5, SQUARE_SIZE});
    hardModeButton->setPosition(GAME_BORDER_RIGHT * SQUARE_SIZE, (GAME_BORDER_TOP + 2) * SQUARE_SIZE);
    hardModeButton->setCallback([this]() {
        mContext->difficulty = DIFFICULTY_HARD;
        mContext->manager.addState(StateRef(new GameState(mContext)), true);
    });

    auto customModeButton = std::make_shared<Button>();
    customModeButton->setTexture(mContext->assets.getTexture("difficultMenuButtons"));
    customModeButton->setNormalTextureRect({SQUARE_SIZE * 0, SQUARE_SIZE * 3, SQUARE_SIZE * 5, SQUARE_SIZE});
    customModeButton->setSelectedTextureRect({SQUARE_SIZE * 5, SQUARE_SIZE * 3, SQUARE_SIZE * 5, SQUARE_SIZE});
    customModeButton->setPosition(GAME_BORDER_RIGHT * SQUARE_SIZE, (GAME_BORDER_TOP + 4) * SQUARE_SIZE);
    customModeButton->setCallback([this]() {
        mContext->manager.addState(StateRef(new CustomDifficultyState(mContext)), true);
    });

    mGuiContainer.pack(mainMenuButton);
    mGuiContainer.pack(exitButton);
    mGuiContainer.pack(customModeButton);
    mGuiContainer.pack(easyModeButton);
    mGuiContainer.pack(normalModeButton);
    mGuiContainer.pack(hardModeButton);
}

void DifficultyMenuState::handleInput() {
    sf::Event event;

    while (mContext->window.pollEvent(event)) {
        mGuiContainer.handleEvent(event);
    }
}


void DifficultyMenuState::update() {

}

void DifficultyMenuState::draw() {
    mContext->window.clear(sf::Color::Red);

    mContext->window.draw(mBackground);
    mContext->window.draw(mGuiContainer);

    mContext->window.display();
}