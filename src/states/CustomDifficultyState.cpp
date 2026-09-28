#include "CustomDifficultyState.hpp"

#include <string>
#include "Difficulty.hpp"
#include "GameContext.hpp"
#include "Layout.hpp"
#include "WindowUtils.hpp"
#include "gui/Button.hpp"
#include "gui/TopBar.hpp"
#include "managers/ResourceIdentifiers.hpp"

namespace {
    constexpr int kWindowTilesX = 7;
    constexpr int kWindowTilesY = 12;

    constexpr int kInputTilesX = 5;
    constexpr int kInputTilesY = 2;

    constexpr int kButtonTilesX = 5;
    constexpr int kButtonTilesY = 1;

    bool tryParseInt(const sf::String& string, int& out) {
        const std::string str = string.toAnsiString();
        if (str.empty()) {
            return false;
        }
        try {
            std::size_t pos = 0;
            const int value = std::stoi(str, &pos);
            if (pos != str.size()) {
                return false;
            }
            out = value;
            return true;
        } catch (const std::exception&) {
            return false;
        }
    }
}

CustomDifficultyState::CustomDifficultyState(GameContext& context)
    : State(context)
    , mWidthInput(std::make_shared<Input>())
    , mHeightInput(std::make_shared<Input>())
    , mMinesInput(std::make_shared<Input>()) {}

void CustomDifficultyState::init() {
    constexpr auto windowSize = Layout::toWindowSize(kWindowTilesX, kWindowTilesY);
    resizeWindow(getContext().window, windowSize);

    auto& backgroundTexture = getContext().assets.getTexture(TextureID::Background);
    mBackground.setTexture(backgroundTexture);
    mBackground.setTextureRect(Layout::getRect(0, 0, kWindowTilesX, kWindowTilesY));

    const auto topBar = std::make_shared<TopBar>(getContext(), kWindowTilesX);

    const auto& buttonsTexture = getContext().assets.getTexture(TextureID::CustomDifficultyButtons);
    const auto& font = getContext().assets.getFont(FontID::Default);

    auto filterOnlyNumbers = [](const char32_t unicode) {
        return unicode >= U'0' && unicode <= U'9';
    };

    mWidthInput->setTexture(buttonsTexture);
    mWidthInput->setPosition(Layout::toPixels(1, 2));
    mWidthInput->setNormalTextureRect(Layout::getRect(0, 0, kInputTilesX, kInputTilesY));
    mWidthInput->setSelectedTextureRect(Layout::getRect(5, 0, kInputTilesX, kInputTilesY));
    mWidthInput->setFont(font);
    mWidthInput->setCharacterSize(32);
    mWidthInput->setStyle(sf::Text::Bold);
    mWidthInput->setFillColor(sf::Color::Green);
    mWidthInput->setInputLimit(2);
    mWidthInput->setInputFilterCallback(filterOnlyNumbers);
    mWidthInput->setInputValidationCallback([](const sf::String& string) {
        int value = 0;
        return tryParseInt(string, value) && value >= Difficulty::Limits::MinWidth && value <= Difficulty::Limits::MaxWidth;
    });

    mHeightInput->setTexture(buttonsTexture);
    mHeightInput->setPosition(Layout::toPixels(1, 4));
    mHeightInput->setNormalTextureRect(Layout::getRect(0, 2, kInputTilesX, kInputTilesY));
    mHeightInput->setSelectedTextureRect(Layout::getRect(5, 2, kInputTilesX, kInputTilesY));
    mHeightInput->setFont(font);
    mHeightInput->setCharacterSize(32);
    mHeightInput->setStyle(sf::Text::Bold);
    mHeightInput->setFillColor(sf::Color::Green);
    mHeightInput->setInputLimit(2);
    mHeightInput->setInputFilterCallback(filterOnlyNumbers);
    mHeightInput->setInputValidationCallback([](const sf::String& string) {
        int value = 0;
        return tryParseInt(string, value) && value >= Difficulty::Limits::MinHeight && value <= Difficulty::Limits::MaxHeight;
    });

    mMinesInput->setTexture(buttonsTexture);
    mMinesInput->setPosition(Layout::toPixels(1, 6));
    mMinesInput->setNormalTextureRect(Layout::getRect(0, 4, kInputTilesX, kInputTilesY));
    mMinesInput->setSelectedTextureRect(Layout::getRect(5, 4, kInputTilesX, kInputTilesY));
    mMinesInput->setFont(font);
    mMinesInput->setCharacterSize(32);
    mMinesInput->setStyle(sf::Text::Bold);
    mMinesInput->setFillColor(sf::Color::Green);
    mMinesInput->setInputLimit(3);
    mMinesInput->setInputFilterCallback(filterOnlyNumbers);
    mMinesInput->setInputValidationCallback([](const sf::String& string) {
        int value = 0;
        return tryParseInt(string, value) && value >= Difficulty::Limits::MinMines && value <= Difficulty::Limits::maxMinesFor(Difficulty::Limits::MaxWidth, Difficulty::Limits::MaxHeight);
    });

    const auto playButton = std::make_shared<Button>();
    playButton->setTexture(buttonsTexture);
    playButton->setNormalTextureRect(Layout::getRect(0, 6, kButtonTilesX, kButtonTilesY));
    playButton->setSelectedTextureRect(Layout::getRect(5, 6, kButtonTilesX, kButtonTilesY));
    playButton->setPosition(Layout::toPixels(1, 9));
    playButton->setCallback([this]() {
        if (mIsFormValid) {
            int width = 0;
            int height = 0;
            int mines = 0;
            if (tryParseInt(mWidthInput->getString(), width) &&
                tryParseInt(mHeightInput->getString(), height) &&
                tryParseInt(mMinesInput->getString(), mines)) {
                if (const auto customDifficulty = Difficulty::createCustom(width, height, mines)) {
                    getContext().difficulty = *customDifficulty;
                    getContext().states.changeState(StateID::Game);
                }
            }
        }
    });

    mGuiContainer.pack(topBar);
    mGuiContainer.pack(mWidthInput);
    mGuiContainer.pack(mHeightInput);
    mGuiContainer.pack(mMinesInput);
    mGuiContainer.pack(playButton);
}

void CustomDifficultyState::handleInput() {
    while (const std::optional<sf::Event> event = getContext().window.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            getContext().window.close();
            return;
        }
        mGuiContainer.handleEvent(*event);
    }
}

void CustomDifficultyState::update() {
    int width = 0;
    int height = 0;
    int mines = 0;
    if (mWidthInput->isValid() && mHeightInput->isValid() && mMinesInput->isValid()
        && tryParseInt(mWidthInput->getString(), width)
        && tryParseInt(mHeightInput->getString(), height)
        && tryParseInt(mMinesInput->getString(), mines)) {
        if (Difficulty::isValid(width, height, mines)) {
            mIsFormValid = true;
        } else {
            mMinesInput->setInvalid();
            mIsFormValid = false;
        }
    } else {
        mIsFormValid = false;
    }
}

void CustomDifficultyState::draw() {
    getContext().window.clear(sf::Color(30, 30, 30));

    getContext().window.draw(mBackground);
    getContext().window.draw(mGuiContainer);

    getContext().window.display();
}
