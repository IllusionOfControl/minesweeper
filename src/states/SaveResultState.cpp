#include "SaveResultState.hpp"

#include <fmt/format.h>

#include "GameContext.hpp"
#include "Layout.hpp"
#include "WindowUtils.hpp"
#include "gui/TopBar.hpp"
#include "managers/ResourceIdentifiers.hpp"
#include "managers/ResultManager.hpp"

namespace {
    constexpr int kWindowTilesX = 8;
    constexpr int kWindowTilesY = 10;

    constexpr int kContentTilesX = 6;
    constexpr int kContentTilesY = 1;
}

SaveResultState::SaveResultState(GameContext& context)
    : State(context) {}

void SaveResultState::init() {
    if (!getContext().lastResult.has_value() || !getContext().lastResult->won) {
        getContext().states.changeState(StateID::MainMenu);
        return;
    }

    constexpr auto windowSize = Layout::toWindowSize(kWindowTilesX, kWindowTilesY);
    resizeWindow(getContext().window, windowSize);

    auto& backgroundTexture = getContext().assets.getTexture(TextureID::Background);
    mBackground.setTexture(backgroundTexture);
    mBackground.setTextureRect(Layout::getRect(0, 0, kWindowTilesX, kWindowTilesY));

    const auto topBar = std::make_shared<TopBar>(getContext(), kWindowTilesX);

    const auto& saveRecordTexture = getContext().assets.getTexture(TextureID::SaveRecordState);
    const auto& ledTexture = getContext().assets.getTexture(TextureID::LedBackground);
    const auto& font = getContext().assets.getFont(FontID::Default);

    const auto result = *getContext().lastResult;

    mTimeLabel = std::make_shared<Image>();
    mTimeLabel->setTexture(saveRecordTexture);
    mTimeLabel->setTextureRect(sf::IntRect({192, 32}, {192, 32}));
    mTimeLabel->setPosition(Layout::toPixels(1, 2));

    mTimeBackground = std::make_shared<Image>();
    mTimeBackground->setTexture(ledTexture);
    mTimeBackground->setTextureRect(Layout::getRect(0, 0, kContentTilesX, kContentTilesY));
    mTimeBackground->setPosition(Layout::toPixels(1, 3));

    mTimeText = std::make_shared<Text>(font, fmt::format("{:03d} SEC", result.timeSeconds), 22);
    mTimeText->setStyle(sf::Text::Bold);
    mTimeText->setFillColor(sf::Color::Red);
    mTimeText->setTextRect(Layout::getRect(1, 3, kContentTilesX, kContentTilesY));
    mTimeText->align(Text::AlignH::Center, Text::AlignV::Center);

    mNameLabel = std::make_shared<Image>();
    mNameLabel->setTexture(saveRecordTexture);
    mNameLabel->setTextureRect(sf::IntRect({192, 0}, {192, 32}));
    mNameLabel->setPosition(Layout::toPixels(1, 5));

    mNameInput = std::make_shared<Input>();
    mNameInput->setTexture(ledTexture);
    mNameInput->setTextureRect(Layout::getRect(0, 0, kContentTilesX, kContentTilesY));
    mNameInput->setPosition(Layout::toPixels(1, 6));
    mNameInput->setFont(font);
    mNameInput->setCharacterSize(22);
    mNameInput->setTextOffset({16.f, 2.f});
    mNameInput->setStyle(sf::Text::Bold);
    mNameInput->setFillColor(sf::Color::White);
    mNameInput->setInputLimit(12);
    mNameInput->setString("PLAYER");
    mNameInput->setInputFilterCallback([](const char32_t unicode) {
        return (unicode >= U'a' && unicode <= U'z') ||
               (unicode >= U'A' && unicode <= U'Z') ||
               (unicode >= U'0' && unicode <= U'9') ||
               unicode == U'_' || unicode == U' ';
    });
    mNameInput->setInputValidationCallback([](const sf::String& string) {
        return !string.isEmpty();
    });

    mSaveButton = std::make_shared<Button>();
    mSaveButton->setTexture(saveRecordTexture);
    mSaveButton->setNormalTextureRect(sf::IntRect({0, 0}, {192, 32}));
    mSaveButton->setSelectedTextureRect(sf::IntRect({0, 32}, {192, 32}));
    mSaveButton->setPosition(Layout::toPixels(1, 8));
    mSaveButton->setCallback([this]() {
        save();
        getContext().states.changeState(StateID::MainMenu);
    });

    mGuiContainer.pack(topBar);
    mGuiContainer.pack(mTimeLabel);
    mGuiContainer.pack(mTimeBackground);
    mGuiContainer.pack(mTimeText);
    mGuiContainer.pack(mNameLabel);
    mGuiContainer.pack(mNameInput);
    mGuiContainer.pack(mSaveButton);
}

void SaveResultState::handleInput() {
    while (const std::optional<sf::Event> event = getContext().window.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            getContext().window.close();
            return;
        }

        mGuiContainer.handleEvent(*event);

        if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
            if (keyPressed->code == sf::Keyboard::Key::Enter) {
                save();
                getContext().states.changeState(StateID::MainMenu);
                return;
            }
        }
    }
}

void SaveResultState::update() {}

void SaveResultState::draw() {
    getContext().window.clear(sf::Color::Red);

    getContext().window.draw(mBackground);
    getContext().window.draw(mGuiContainer);

    getContext().window.display();
}

void SaveResultState::save() {
    if (mSaved) {
        return;
    }

    if (!getContext().lastResult.has_value() || !getContext().lastResult->won) {
        return;
    }

    auto result = *getContext().lastResult;
    const auto name = mNameInput->getString().toAnsiString();
    if (!name.empty()) {
        result.playerName = name;
    }
    if (result.date.empty()) {
        result.date = ResultManager::getCurrentDateTime();
    }

    if (ResultManager::saveResult(result)) {
        mSaved = true;
    }
}
