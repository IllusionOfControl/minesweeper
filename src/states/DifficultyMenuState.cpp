#include "DifficultyMenuState.hpp"
#include "../gui/Button.hpp"

DifficultyMenuState::DifficultyMenuState(GameDataRef data)
        : mGameData(data)
        , mGuiContainer() {

}

void DifficultyMenuState::Init() {
    mGameData->window.create(sf::VideoMode((WIDTH + GAME_BORDER_RIGHT + GAME_BORDER_LEFT) * SQUARE_SIZE,
                                                 (HEIGHT + GAME_BORDER_TOP + GAME_BORDER_BOTTOM) * SQUARE_SIZE),
                                   "Minesweeper",
                                   sf::Style::Titlebar | sf::Style::Close);
    auto &backgroundTexture = mGameData->assets.GetTexture("background");
    auto windowSize = mGameData->window.getSize();

    backgroundTexture.setRepeated(true);
    mBackground.setTexture(backgroundTexture);
    mBackground.setTextureRect({0, 0, (int) windowSize.x, (int) windowSize.y});

    auto mainMenuButton = std::make_shared<Button>();
    mainMenuButton->setTexture(mGameData->assets.GetTexture("state_buttons"));
    mainMenuButton->setNormalTextureRect({0, 0, SQUARE_SIZE, SQUARE_SIZE});
    mainMenuButton->setSelectedTextureRect({SQUARE_SIZE * 1, 0, SQUARE_SIZE, SQUARE_SIZE});
    mainMenuButton->setPosition(0 * SQUARE_SIZE, 0 * SQUARE_SIZE);
    mainMenuButton->setCallback([&]() {
        mGameData->manager.AddState(StateRef(new MainMenuState(mGameData)), true);
    });

    auto exitButton = std::make_shared<Button>();
    exitButton->setTexture(mGameData->assets.GetTexture("state_buttons"));
    exitButton->setNormalTextureRect({SQUARE_SIZE * 2, 0, SQUARE_SIZE, SQUARE_SIZE});
    exitButton->setSelectedTextureRect({SQUARE_SIZE * 3, 0, SQUARE_SIZE, SQUARE_SIZE});
    exitButton->setPosition((WIDTH + GAME_BORDER_RIGHT) * SQUARE_SIZE, 0);
    exitButton->setCallback([&]() {
        mGameData->window.close();
    });

    auto easyModeButton = std::make_shared<Button>();
    easyModeButton->setTexture(mGameData->assets.GetTexture("difficultMenuButtons"));
    easyModeButton->setNormalTextureRect({0, 0, SQUARE_SIZE * 5, SQUARE_SIZE});
    easyModeButton->setSelectedTextureRect({SQUARE_SIZE * 5, 0, SQUARE_SIZE * 5, SQUARE_SIZE});
    easyModeButton->setPosition(GAME_BORDER_RIGHT * SQUARE_SIZE, (GAME_BORDER_TOP - 2) * SQUARE_SIZE);
    easyModeButton->setCallback([&]() {
        mGameData->difficulty = DIFFICULTY_EASY;
        mGameData->manager.AddState(StateRef(new GameState(mGameData)), true);
    });


    auto normalModeButton = std::make_shared<Button>();
    normalModeButton->setTexture(mGameData->assets.GetTexture("difficultMenuButtons"));
    normalModeButton->setNormalTextureRect({SQUARE_SIZE * 0, SQUARE_SIZE * 1, SQUARE_SIZE * 5, SQUARE_SIZE});
    normalModeButton->setSelectedTextureRect({SQUARE_SIZE * 5, SQUARE_SIZE * 1, SQUARE_SIZE * 5, SQUARE_SIZE});
    normalModeButton->setPosition(GAME_BORDER_RIGHT * SQUARE_SIZE, GAME_BORDER_TOP * SQUARE_SIZE);
    normalModeButton->setCallback([&]() {
        mGameData->difficulty = DIFFICULTY_MEDIUM;
        mGameData->manager.AddState(StateRef(new GameState(mGameData)), true);
    });

    auto hardModeButton = std::make_shared<Button>();
    hardModeButton->setTexture(mGameData->assets.GetTexture("difficultMenuButtons"));
    hardModeButton->setNormalTextureRect({SQUARE_SIZE * 0, SQUARE_SIZE * 2, SQUARE_SIZE * 5, SQUARE_SIZE});
    hardModeButton->setSelectedTextureRect({SQUARE_SIZE * 5, SQUARE_SIZE * 2, SQUARE_SIZE * 5, SQUARE_SIZE});
    hardModeButton->setPosition(GAME_BORDER_RIGHT * SQUARE_SIZE, (GAME_BORDER_TOP + 2) * SQUARE_SIZE);
    hardModeButton->setCallback([&]() {
        mGameData->difficulty = DIFFICULTY_HARD;
        mGameData->manager.AddState(StateRef(new GameState(mGameData)), true);
    });

    auto customModeButton = std::make_shared<Button>();
    customModeButton->setTexture(mGameData->assets.GetTexture("difficultMenuButtons"));
    customModeButton->setNormalTextureRect({SQUARE_SIZE * 0, SQUARE_SIZE * 3, SQUARE_SIZE * 5, SQUARE_SIZE});
    customModeButton->setSelectedTextureRect({SQUARE_SIZE * 5, SQUARE_SIZE * 3, SQUARE_SIZE * 5, SQUARE_SIZE});
    customModeButton->setPosition(GAME_BORDER_RIGHT * SQUARE_SIZE, (GAME_BORDER_TOP + 4) * SQUARE_SIZE);
    customModeButton->setCallback([&]() {
        mGameData->manager.AddState(StateRef(new CustomDifficultyState(mGameData)), true);
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

    while (mGameData->window.pollEvent(event)) {
        mGuiContainer.handleEvent(event);
    }
}


void DifficultyMenuState::Update() {

}

void DifficultyMenuState::Draw() {
    mGameData->window.clear(sf::Color::Red);

    mGameData->window.draw(mBackground);
    mGameData->window.draw(mGuiContainer);

    mGameData->window.display();
}