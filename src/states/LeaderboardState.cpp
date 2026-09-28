#include "LeaderboardState.hpp"

#include <fmt/format.h>
#include "GameContext.hpp"
#include "Layout.hpp"
#include "WindowUtils.hpp"
#include "gui/TopBar.hpp"
#include "managers/ResourceIdentifiers.hpp"
#include "managers/ResultManager.hpp"

namespace {
    constexpr int kWindowTilesX = 13;
    constexpr int kWindowTilesY = 15;
    constexpr std::size_t kMaxRecordsShown = 8;
}

LeaderboardState::LeaderboardState(GameContext& context)
    : State(context)
      , mDifficultyFilters{"Easy", "Medium", "Hard", "Custom", "All"} {}

void LeaderboardState::init() {
    constexpr auto windowSize = Layout::toWindowSize(kWindowTilesX, kWindowTilesY);
    resizeWindow(getContext().window, windowSize);

    auto& backgroundTexture = getContext().assets.getTexture(TextureID::Background);
    mBackground.setTexture(backgroundTexture);
    mBackground.setTextureRect(Layout::getRect(0, 0, kWindowTilesX, kWindowTilesY));

    if (getContext().lastResult.has_value()) {
        const auto& diff = getContext().lastResult->difficulty;
        for (std::size_t i = 0; i < mDifficultyFilters.size(); ++i) {
            if (mDifficultyFilters[i] == diff) {
                mCurrentFilterIndex = i;
                break;
            }
        }
    }

        mGuiContainer = Container{};

    const auto topBar = std::make_shared<TopBar>(getContext(), kWindowTilesX);
    mGuiContainer.pack(topBar);

    const auto& font = getContext().assets.getFont(FontID::Default);
    const auto& tilesTexture = getContext().assets.getTexture(TextureID::Tiles);
    const auto& cleanTileBackground = getContext().assets.getTexture(TextureID::CleanTileBackground);

    const auto titleText = std::make_shared<Text>(font, "LEADERBOARD", 26);
    titleText->setStyle(sf::Text::Bold);
    titleText->setFillColor(sf::Color(255, 215, 0));
    titleText->setTextRect(Layout::getRect(0, 1, kWindowTilesX, 1));
    titleText->align(Text::AlignH::Center, Text::AlignV::Center);
    mGuiContainer.pack(titleText);

    const auto prevFilterBtn = std::make_shared<Button>();
    prevFilterBtn->setTexture(tilesTexture);
    prevFilterBtn->setNormalTextureRect(Layout::getRect(11, 0, 1, 1));
    prevFilterBtn->setSelectedTextureRect(Layout::getRect(0, 0, 1, 1));
    prevFilterBtn->setPosition(Layout::toPixels(1, 2));
    prevFilterBtn->setText(font, "<", 18, sf::Color::Black, sf::Color::Red);
    prevFilterBtn->setCallback([this]() { switchDifficulty(-1); });
    mGuiContainer.pack(prevFilterBtn);

    mFilterTextBackground = std::make_shared<Image>();
    mFilterTextBackground->setTexture(cleanTileBackground);
    mFilterTextBackground->setTextureRect(Layout::getRect(0, 0, 9, 1));
    mFilterTextBackground->setPosition(Layout::toPixels(2, 2));
    mGuiContainer.pack(mFilterTextBackground);

    mFilterText = std::make_shared<Text>(font, "", 20);
    mFilterText->setStyle(sf::Text::Bold);
    mFilterText->setFillColor(sf::Color::White);
    mFilterText->setTextRect(Layout::getRect(2, 2, kWindowTilesX - 4, 1));
    mFilterText->align(Text::AlignH::Center, Text::AlignV::Center);
    mGuiContainer.pack(mFilterText);

    const auto nextFilterBtn = std::make_shared<Button>();
    nextFilterBtn->setTexture(tilesTexture);
    nextFilterBtn->setNormalTextureRect(Layout::getRect(11, 0, 1, 1));
    nextFilterBtn->setSelectedTextureRect(Layout::getRect(0, 0, 1, 1));
    nextFilterBtn->setPosition(Layout::toPixels(kWindowTilesX - 2, 2));
    nextFilterBtn->setText(font, ">", 18, sf::Color::Black, sf::Color::Red);
    nextFilterBtn->setCallback([this]() { switchDifficulty(1); });
    mGuiContainer.pack(nextFilterBtn);

    mLeaderTableBackground = std::make_shared<Image>();
    mLeaderTableBackground->setTexture(cleanTileBackground);
    mLeaderTableBackground->setTextureRect(Layout::getRect(0, 0, 11, 11));
    mLeaderTableBackground->setPosition(Layout::toPixels(1, 3));
    mGuiContainer.pack(mLeaderTableBackground);

    mHeaderRowText = std::make_shared<Text>(font, "#   NAME                TIME", 18);
    mHeaderRowText->setStyle(sf::Text::Bold);
    mHeaderRowText->setFillColor(sf::Color(170, 170, 170));
    mHeaderRowText->setPosition(Layout::toPixels(1, 3));
    mHeaderRowText->setTextRect(Layout::getRect(1, 3, 11, 1));
    mHeaderRowText->align();
    mGuiContainer.pack(mHeaderRowText);

    mRecordRowTexts.clear();
    for (std::size_t i = 0; i < kMaxRecordsShown; ++i) {
        auto rowText = std::make_shared<Text>(font, "", 18);
        const auto tileOffsetY = 4 + static_cast<int>(i);
        rowText->setStyle(sf::Text::Bold);
        rowText->setPosition(Layout::toPixels(1, tileOffsetY));
        rowText->setTextRect(Layout::getRect(1, tileOffsetY, 11, 1));
        rowText->alignHorizontal(Text::AlignH::Left, Layout::TileSize / 4.f);
        mRecordRowTexts.push_back(rowText);
        mGuiContainer.pack(rowText);
    }

    mStatusMessageText = std::make_shared<Text>(font, "", 18);
    mStatusMessageText->setStyle(sf::Text::Bold);
    mStatusMessageText->setFillColor(sf::Color::White);
    mStatusMessageText->setTextRect(Layout::getRect(1, 4, 11, 9));
    mStatusMessageText->align(Text::AlignH::Center, Text::AlignV::Center);
    mGuiContainer.pack(mStatusMessageText);

    refreshRecords();
}

void LeaderboardState::switchDifficulty(const int direction) {
    if (mDifficultyFilters.empty()) return;
    const int count = static_cast<int>(mDifficultyFilters.size());
    const int newIndex = (static_cast<int>(mCurrentFilterIndex) + direction + count) % count;
    mCurrentFilterIndex = static_cast<std::size_t>(newIndex);
    refreshRecords();
}

void LeaderboardState::refreshRecords() const {
    const std::string filter = mDifficultyFilters[mCurrentFilterIndex];
    if (mFilterText) {
        mFilterText->setString(std::string_view(fmt::format("DIFFICULTY: {}", filter)));
        mFilterText->align(Text::AlignH::Center, Text::AlignV::Center);
    }

    const auto topResults = ResultManager::getTopResults(filter, kMaxRecordsShown);

    for (std::size_t i = 0; i < kMaxRecordsShown; ++i) {
        if (i < topResults.size()) {
            const auto& r = topResults[i];

            std::string name = r.playerName;
            if (name.size() > 10) { name = name.substr(0, 9) + "."; }

            const auto rowStr = fmt::format("{:<2}  {:<10}           {:>3}s", i + 1, name, r.timeSeconds);
            mRecordRowTexts[i]->setString(std::string_view(rowStr));

            if (i == 0) { mRecordRowTexts[i]->setFillColor(sf::Color(255, 215, 0)); } else if (i == 1) {
                mRecordRowTexts[i]->setFillColor(sf::Color(215, 215, 215));
            } else if (i == 2) { mRecordRowTexts[i]->setFillColor(sf::Color(220, 150, 90)); } else {
                mRecordRowTexts[i]->setFillColor(sf::Color::White);
            }
        } else { mRecordRowTexts[i]->setString(std::string_view("")); }
    }

    if (topResults.empty()) {
        mStatusMessageText->setString(std::string_view("NO RECORDS YET"));
        mStatusMessageText->align(Text::AlignH::Center, Text::AlignV::Center);
    } else { mStatusMessageText->setString(std::string_view("")); }
}

void LeaderboardState::handleInput() {
    while (const std::optional<sf::Event> event = getContext().window.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            getContext().window.close();
            return;
        }
        mGuiContainer.handleEvent(*event);
    }
}

void LeaderboardState::update() {}

void LeaderboardState::draw() {
    getContext().window.clear(sf::Color(30, 30, 30));
    getContext().window.draw(mBackground);
    getContext().window.draw(mGuiContainer);
    getContext().window.display();
}
