#include "DifficultyMenuState.hpp"
#include "../gui/Button.hpp"

DifficultyMenuState::DifficultyMenuState(GameDataRef context)
        : mContext(context)
        , mGuiContainer() {

}

void DifficultyMenuState::Init() {
    mContext->window.create(sf::VideoMode((WIDTH + GAME_BORDER_RIGHT + GAME_BORDER_LEFT) * SQUARE_SIZE,
                                                 (HEIGHT + GAME_BORDER_TOP + GAME_BORDER_BOTTOM) * SQUARE_SIZE),
                            "Minesweeper",
                                   sf::Style::Titlebar | sf::Style::Close);
    auto &backgroundTexture = mContext->assets.GetTexture("background");
    auto windowSize = mContext->window.getSize();

    backgroundTexture.setRepeated(true);
    mBackground.setTexture(backgroundTexture);
    mBackground.setTextureRect({0, 0, (int) windowSize.x, (int) windowSize.y});

    auto mainMenuButton = std::make_shared<Button>();
    mainMenuButton->setTexture(mContext->assets.GetTexture("state_buttons"));
    mainMenuButton->setNormalTextureRect({0, 0, SQUARE_SIZE, SQUARE_SIZE});
    mainMenuButton->setSelectedTextureRect({SQUARE_SIZE * 1, 0, SQUARE_SIZE, SQUARE_SIZE});
    mainMenuButton->setPosition(0 * SQUARE_SIZE, 0 * SQUARE_SIZE);
    mainMenuButton->setCallback([&]() {
        mContext->manager.AddState(StateRef(new MainMenuState(mContext)), true);
    });

    auto exitButton = std::make_shared<Button>();
    exitButton->setTexture(mContext->assets.GetTexture("state_buttons"));
    exitButton->setNormalTextureRect({SQUARE_SIZE * 2, 0, SQUARE_SIZE, SQUARE_SIZE});
    exitButton->setSelectedTextureRect({SQUARE_SIZE * 3, 0, SQUARE_SIZE, SQUARE_SIZE});
    exitButton->setPosition((WIDTH + GAME_BORDER_RIGHT) * SQUARE_SIZE, 0);
    exitButton->setCallback([&]() {
        mContext->window.close();
    });

    auto easyModeButton = std::make_shared<Button>();
    easyModeButton->setTexture(mContext->assets.GetTexture("difficultMenuButtons"));
    easyModeButton->setNormalTextureRect({0, 0, SQUARE_SIZE * 5, SQUARE_SIZE});
    easyModeButton->setSelectedTextureRect({SQUARE_SIZE * 5, 0, SQUARE_SIZE * 5, SQUARE_SIZE});
    easyModeButton->setPosition(GAME_BORDER_RIGHT * SQUARE_SIZE, (GAME_BORDER_TOP - 2) * SQUARE_SIZE);
    easyModeButton->setCallback([&]() {
        mContext->difficulty = DIFFICULTY_EASY;
        mContext->manager.AddState(StateRef(new GameState(mContext)), true);
    });


    auto normalModeButton = std::make_shared<Button>();
    normalModeButton->setTexture(mContext->assets.GetTexture("difficultMenuButtons"));
    normalModeButton->setNormalTextureRect({SQUARE_SIZE * 0, SQUARE_SIZE * 1, SQUARE_SIZE * 5, SQUARE_SIZE});
    normalModeButton->setSelectedTextureRect({SQUARE_SIZE * 5, SQUARE_SIZE * 1, SQUARE_SIZE * 5, SQUARE_SIZE});
    normalModeButton->setPosition(GAME_BORDER_RIGHT * SQUARE_SIZE, GAME_BORDER_TOP * SQUARE_SIZE);
    normalModeButton->setCallback([&]() {
        mContext->difficulty = DIFFICULTY_MEDIUM;
        mContext->manager.AddState(StateRef(new GameState(mContext)), true);
    });

    auto hardModeButton = std::make_shared<Button>();
    hardModeButton->setTexture(mContext->assets.GetTexture("difficultMenuButtons"));
    hardModeButton->setNormalTextureRect({SQUARE_SIZE * 0, SQUARE_SIZE * 2, SQUARE_SIZE * 5, SQUARE_SIZE});
    hardModeButton->setSelectedTextureRect({SQUARE_SIZE * 5, SQUARE_SIZE * 2, SQUARE_SIZE * 5, SQUARE_SIZE});
    hardModeButton->setPosition(GAME_BORDER_RIGHT * SQUARE_SIZE, (GAME_BORDER_TOP + 2) * SQUARE_SIZE);
    hardModeButton->setCallback([&]() {
        mContext->difficulty = DIFFICULTY_HARD;
        mContext->manager.AddState(StateRef(new GameState(mContext)), true);
    });

    auto customModeButton = std::make_shared<Button>();
    customModeButton->setTexture(mContext->assets.GetTexture("difficultMenuButtons"));
    customModeButton->setNormalTextureRect({SQUARE_SIZE * 0, SQUARE_SIZE * 3, SQUARE_SIZE * 5, SQUARE_SIZE});
    customModeButton->setSelectedTextureRect({SQUARE_SIZE * 5, SQUARE_SIZE * 3, SQUARE_SIZE * 5, SQUARE_SIZE});
    customModeButton->setPosition(GAME_BORDER_RIGHT * SQUARE_SIZE, (GAME_BORDER_TOP + 4) * SQUARE_SIZE);
    customModeButton->setCallback([&]() {
        mContext->manager.AddState(StateRef(new CustomDifficultyState(mContext)), true);
    });

    mGuiContainer.pack(mainMenuButton);
    mGuiContainer.pack(exitButton);
    mGuiContainer.pack(customModeButton);
    mGuiContainer.pack(easyModeButton);
    mGuiContainer.pack(normalModeButton);
    mGuiContainer.pack(hardModeButton);
}

void DifficultyMenuState::HandleInput() {
    sf::Event event;

    while (mContext->window.pollEvent(event)) {
        mGuiContainer.handleEvent(event);
    }
}


void DifficultyMenuState::Update() {

}

void DifficultyMenuState::Draw() {
    mContext->window.clear(sf::Color::Red);

    mContext->window.draw(mBackground);
    mContext->window.draw(mGuiContainer);

    mContext->window.display();
}