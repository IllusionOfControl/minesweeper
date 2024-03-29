#include <sstream>
#include <string>
#include "CustomDifficultyState.hpp"
#include "../gui/Button.hpp"

CustomDifficultyState::CustomDifficultyState(GameDataRef context)
        : mContext(context)
        , mWidthInput(std::make_shared<Input>())
        , mHeightInput(std::make_shared<Input>())
        , mMinesInput(std::make_shared<Input>())
        , mIsFormValid(false) {
}

void CustomDifficultyState::init() {
    mContext->window.create(sf::VideoMode((WIDTH + GAME_BORDER_RIGHT + GAME_BORDER_LEFT) * SQUARE_SIZE,
                                                 (HEIGHT + GAME_BORDER_TOP + GAME_BORDER_BOTTOM) * SQUARE_SIZE),
                            "Minesweeper",
                                   sf::Style::Titlebar | sf::Style::Close);
    auto &backgroundTexture = mContext->assets.getTexture("background");
    auto windowSize = mContext->window.getSize();

    backgroundTexture.setRepeated(true);
    mBackground.setTexture(backgroundTexture);
    mBackground.setTextureRect({0, 0, (int) windowSize.x, (int) windowSize.y});

    //

    auto mainMenuButton = std::make_shared<Button>();
    mainMenuButton->setTexture(mContext->assets.getTexture("state_buttons"));
    mainMenuButton->setNormalTextureRect({0, 0, SQUARE_SIZE, SQUARE_SIZE});
    mainMenuButton->setSelectedTextureRect({SQUARE_SIZE * 1, 0, SQUARE_SIZE, SQUARE_SIZE});
    mainMenuButton->setPosition(0 * SQUARE_SIZE, 0 * SQUARE_SIZE);
    mainMenuButton->setCallback([&]() {
        mContext->manager.addState(StateRef(new MainMenuState(mContext)), true);
    });

    auto exitButton = std::make_shared<Button>();
    exitButton->setTexture(mContext->assets.getTexture("state_buttons"));
    exitButton->setNormalTextureRect({SQUARE_SIZE * 2, 0, SQUARE_SIZE, SQUARE_SIZE});
    exitButton->setSelectedTextureRect({SQUARE_SIZE * 3, 0, SQUARE_SIZE, SQUARE_SIZE});
    exitButton->setPosition((WIDTH + GAME_BORDER_RIGHT) * SQUARE_SIZE, 0);
    exitButton->setCallback([&]() {
        mContext->window.close();
    });

    std::function<bool(sf::Uint32)> filterOnlyNumbers = [](sf::Uint32 unicode) {
        if (unicode >= 0x30 && unicode <= 0x39)
            return true;
        return false;
    };

    mWidthInput->setTexture(mContext->assets.getTexture("customDifficultyButtons"));
    mWidthInput->setPosition(GAME_BORDER_RIGHT * SQUARE_SIZE, (GAME_BORDER_TOP - 2) * SQUARE_SIZE);
    mWidthInput->setNormalTextureRect({0, 0, SQUARE_SIZE * 5, SQUARE_SIZE * 2});
    mWidthInput->setSelectedTextureRect({SQUARE_SIZE * 5, 0, SQUARE_SIZE * 5, SQUARE_SIZE * 2});
    mWidthInput->setFont(mContext->assets.GetFont("default_font"));
    mWidthInput->setCharacterSize(32);
    mWidthInput->setStyle(sf::Text::Bold);
    mWidthInput->setFillColor(sf::Color::Green);
    mWidthInput->setInputLimit(2);
    mWidthInput->setInputFilterCallback(filterOnlyNumbers);
    mWidthInput->setInputValidationCallback([](const sf::String &string) {
        int value = std::stoi(string.toAnsiString());
        if (value >= 5 && value <= 18)
            return true;
        return false;
    });

    mHeightInput->setTexture(mContext->assets.getTexture("customDifficultyButtons"));
    mHeightInput->setPosition(GAME_BORDER_RIGHT * SQUARE_SIZE, (GAME_BORDER_TOP) * SQUARE_SIZE);
    mHeightInput->setNormalTextureRect({0, SQUARE_SIZE * 2, SQUARE_SIZE * 5, SQUARE_SIZE * 2});
    mHeightInput->setSelectedTextureRect({SQUARE_SIZE * 5, SQUARE_SIZE * 2, SQUARE_SIZE * 5, SQUARE_SIZE * 2});
    mHeightInput->setFont(mContext->assets.GetFont("default_font"));
    mHeightInput->setCharacterSize(32);
    mHeightInput->setStyle(sf::Text::Bold);
    mHeightInput->setFillColor(sf::Color::Green);
    mHeightInput->setInputLimit(2);
    mHeightInput->setInputFilterCallback(filterOnlyNumbers);
    mHeightInput->setInputValidationCallback([](const sf::String &string) {
        int value = std::stoi(string.toAnsiString());
        if (value >= 5 && value <= 18)
            return true;
        return false;
    });

    mMinesInput->setTexture(mContext->assets.getTexture("customDifficultyButtons"));
    mMinesInput->setPosition(GAME_BORDER_RIGHT * SQUARE_SIZE, (GAME_BORDER_TOP + 2) * SQUARE_SIZE);
    mMinesInput->setNormalTextureRect({0, SQUARE_SIZE * 4, SQUARE_SIZE * 5, SQUARE_SIZE * 2});
    mMinesInput->setSelectedTextureRect({SQUARE_SIZE * 5, SQUARE_SIZE * 4, SQUARE_SIZE * 5, SQUARE_SIZE * 2});
    mMinesInput->setFont(mContext->assets.GetFont("default_font"));
    mMinesInput->setCharacterSize(32);
    mMinesInput->setStyle(sf::Text::Bold);
    mMinesInput->setFillColor(sf::Color::Green);
    mMinesInput->setInputLimit(3);
    mMinesInput->setInputFilterCallback(filterOnlyNumbers);
    mMinesInput->setInputValidationCallback([](const sf::String &string) {
        int value = std::stoi(string.toAnsiString());
        if (value >= 5 && value <= 320)
            return true;
        return false;
    });

    auto playButton = std::make_shared<Button>();
    playButton->setTexture(mContext->assets.getTexture("customDifficultyButtons"));
    playButton->setNormalTextureRect({0, SQUARE_SIZE * 6, SQUARE_SIZE * 5, SQUARE_SIZE});
    playButton->setSelectedTextureRect({SQUARE_SIZE * 5, SQUARE_SIZE * 6, SQUARE_SIZE * 5, SQUARE_SIZE});
    playButton->setPosition(GAME_BORDER_RIGHT * SQUARE_SIZE, (GAME_BORDER_TOP + 4) * SQUARE_SIZE);
    playButton->setCallback([&]() {
        if (mIsFormValid)
            mContext->manager.addState(StateRef(new GameState(mContext)), true);
    });

    auto &textBackground = mContext->assets.getTexture("text_background");
    textBackground.setRepeated(true);

    mContainer.pack(mainMenuButton);
    mContainer.pack(exitButton);
    mContainer.pack(mWidthInput);
    mContainer.pack(mHeightInput);
    mContainer.pack(mMinesInput);
    mContainer.pack(playButton);
}

void CustomDifficultyState::handleInput() {
    sf::Event event;

    while (mContext->window.pollEvent(event)) {
        mContainer.handleEvent(event);
    }
}

void CustomDifficultyState::update() {
    if (mWidthInput->isValid() && mHeightInput->isValid() && mMinesInput->isValid()) {
        int width = std::stoi(mWidthInput->getString().toAnsiString());
        int height = std::stoi(mHeightInput->getString().toAnsiString());
        int mines = std::stoi(mMinesInput->getString().toAnsiString());

        if (mines < (width * height)) {
            mContext->difficulty.field_width = width;
            mContext->difficulty.field_height = height;
            mContext->difficulty.bomb_count = mines;

            mIsFormValid = true;
        } else {
            mMinesInput->setInvalid();
        }
    } else {
        mIsFormValid = false;
    }
}

void CustomDifficultyState::draw() {
    mContext->window.clear(sf::Color::Red);

    mContext->window.draw(mBackground);
    mContext->window.draw(mContainer);

    mContext->window.display();
}