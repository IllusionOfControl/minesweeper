#include "LeaderboardState.h"


LeaderboardState::LeaderboardState(GameDataRef data) : _data(data)
{

}

void LeaderboardState::Init() {
    this->_data->window.create(sf::VideoMode((WIDTH + GAME_BORDER_RIGHT + GAME_BORDER_LEFT + 6) * SQUARE_SIZE,
                                             (HEIGHT + GAME_BORDER_TOP + GAME_BORDER_BOTTOM) * SQUARE_SIZE),
                               "Minesweeper",
                               sf::Style::Titlebar | sf::Style::Close);
    auto &backgroundTexture = this->_data->assets.GetTexture("background");
    auto windowSize = this->_data->window.getSize();

    backgroundTexture.setRepeated(true);
    this->_background.setTexture(backgroundTexture);
    this->_background.setTextureRect({0, 0, (int) windowSize.x, (int) windowSize.y});

    this->_mainMenuButton.setTexture(this->_data->assets.GetTexture("state_buttons"));
    this->_mainMenuButton.setTextureRect({0, 0, SQUARE_SIZE, SQUARE_SIZE});
    this->_mainMenuButton.setPosition(0 * SQUARE_SIZE, 0 * SQUARE_SIZE);

    this->_exitButton.setTexture(this->_data->assets.GetTexture("state_buttons"));
    this->_exitButton.setTextureRect({SQUARE_SIZE * 2, 0, SQUARE_SIZE, SQUARE_SIZE});
    this->_exitButton.setPosition((WIDTH + GAME_BORDER_RIGHT + 6) * SQUARE_SIZE, 0);

    auto& ledBackground = this->_data->assets.GetTexture("led_background");
    ledBackground.setRepeated(true);
    this->_textBgEasy.setTexture(ledBackground);
    this->_textBgEasy.setTextureRect({0, 0, SQUARE_SIZE * 11, SQUARE_SIZE});
    this->_textBgEasy.setPosition((GAME_BORDER_LEFT) * SQUARE_SIZE, (GAME_BORDER_TOP-1) * SQUARE_SIZE);
    this->_bannerEasy.setTexture(_data->assets.GetTexture("leaderboard"));
    this->_bannerEasy.setTextureRect({0, 0, SQUARE_SIZE * 11, SQUARE_SIZE});
    this->_bannerEasy.setPosition((GAME_BORDER_LEFT) * SQUARE_SIZE, (GAME_BORDER_TOP-2) * SQUARE_SIZE);
    this->_textEasyName.setFont(this->_data->assets.GetFont("default_font"));
    this->_textEasyName.setCharacterSize(20);
    this->_textEasyName.setStyle(sf::Text::Bold);
    this->_textEasyName.setScale(2.f, 2.f);
    this->_textEasyName.setPosition(GAME_BORDER_LEFT * SQUARE_SIZE + 6, (GAME_BORDER_TOP-2) * SQUARE_SIZE + 18);
    this->_textEasyName.setString(_data->leaderboard.records[GAME_EASY].name);
    this->_textEasyTime.setFont(this->_data->assets.GetFont("default_font"));
    this->_textEasyTime.setCharacterSize(20);
    this->_textEasyTime.setStyle(sf::Text::Bold);
    this->_textEasyTime.setScale(2.f, 2.f);
    this->_textEasyTime.setPosition((GAME_BORDER_LEFT + 8) * SQUARE_SIZE + 6, (GAME_BORDER_TOP-2) * SQUARE_SIZE + 18);

    this->_textBgNormal.setTexture(ledBackground);
    this->_textBgNormal.setTextureRect({0, 0, SQUARE_SIZE * 11, SQUARE_SIZE});
    this->_textBgNormal.setPosition((GAME_BORDER_LEFT) * SQUARE_SIZE, (GAME_BORDER_TOP+2) * SQUARE_SIZE);
    this->_bannerNormal.setTexture(_data->assets.GetTexture("leaderboard"));
    this->_bannerNormal.setTextureRect({0, 32, SQUARE_SIZE * 11, SQUARE_SIZE});
    this->_bannerNormal.setPosition((GAME_BORDER_LEFT) * SQUARE_SIZE, (GAME_BORDER_TOP+1) * SQUARE_SIZE);
    this->_textNormalName.setFont(this->_data->assets.GetFont("default_font"));
    this->_textNormalName.setCharacterSize(20);
    this->_textNormalName.setStyle(sf::Text::Bold);
    this->_textNormalName.setScale(2.f, 2.f);
    this->_textNormalName.setPosition(GAME_BORDER_LEFT * SQUARE_SIZE + 6, (GAME_BORDER_TOP+1) * SQUARE_SIZE + 18);
    this->_textNormalName.setString(_data->leaderboard.records[GAME_NORMAL].name);
    this->_textNormalTime.setFont(this->_data->assets.GetFont("default_font"));
    this->_textNormalTime.setCharacterSize(20);
    this->_textNormalTime.setStyle(sf::Text::Bold);
    this->_textNormalTime.setScale(2.f, 2.f);
    this->_textNormalTime.setPosition((GAME_BORDER_LEFT + 8) * SQUARE_SIZE + 6, (GAME_BORDER_TOP+1) * SQUARE_SIZE + 18);

    this->_textBgHard.setTexture(ledBackground);
    this->_textBgHard.setTextureRect({0, 0, SQUARE_SIZE * 11, SQUARE_SIZE});
    this->_textBgHard.setPosition((GAME_BORDER_LEFT) * SQUARE_SIZE, (GAME_BORDER_TOP+5) * SQUARE_SIZE);
    this->_bannerHard.setTexture(_data->assets.GetTexture("leaderboard"));
    this->_bannerHard.setTextureRect({0, 64, SQUARE_SIZE * 11, SQUARE_SIZE});
    this->_bannerHard.setPosition((GAME_BORDER_LEFT) * SQUARE_SIZE, (GAME_BORDER_TOP+4) * SQUARE_SIZE);
    this->_textHardName.setFont(this->_data->assets.GetFont("default_font"));
    this->_textHardName.setCharacterSize(20);
    this->_textHardName.setStyle(sf::Text::Bold);
    this->_textHardName.setScale(2.f, 2.f);
    this->_textHardName.setPosition(GAME_BORDER_LEFT * SQUARE_SIZE + 6, (GAME_BORDER_TOP+4) * SQUARE_SIZE + 18);
    this->_textHardName.setString(_data->leaderboard.records[GAME_HARD].name);
    this->_textHardTime.setFont(this->_data->assets.GetFont("default_font"));
    this->_textHardTime.setCharacterSize(20);
    this->_textHardTime.setStyle(sf::Text::Bold);
    this->_textHardTime.setScale(2.f, 2.f);
    this->_textHardTime.setPosition((GAME_BORDER_LEFT + 8) * SQUARE_SIZE + 6, (GAME_BORDER_TOP+4) * SQUARE_SIZE + 18);

    std::ostringstream time;
    time << _data->leaderboard.records[GAME_EASY].time;
    this->_textEasyTime.setString(time.str());
    time.str("");
    time << _data->leaderboard.records[GAME_NORMAL].time;
    this->_textNormalTime.setString(time.str());
    time.str("");
    time << _data->leaderboard.records[GAME_HARD].time;
    this->_textHardTime.setString(time.str());
    time.str("");
}

void LeaderboardState::HandleInput()
{
    sf::Event event;

    while (this->_data->window.pollEvent(event)) {
        switch (event.type) {
            case sf::Event::Closed:
                this->_data->window.close();
                break;
            case sf::Event::MouseMoved: {
                auto mousePos = sf::Vector2f((float) event.mouseMove.x, (float) event.mouseMove.y);
                if (this->_mainMenuButton.getGlobalBounds().contains(mousePos.x, mousePos.y))
                    this->_mainMenuButton.setTextureRect({SQUARE_SIZE * 1, 0, SQUARE_SIZE, SQUARE_SIZE});
                else this->_mainMenuButton.setTextureRect({0, 0, SQUARE_SIZE, SQUARE_SIZE});

                if (this->_exitButton.getGlobalBounds().contains(sf::Vector2f(mousePos)))
                    this->_exitButton.setTextureRect({SQUARE_SIZE * 3, 0, SQUARE_SIZE, SQUARE_SIZE});
                else this->_exitButton.setTextureRect({SQUARE_SIZE * 2, 0, SQUARE_SIZE, SQUARE_SIZE});
                break;
            }
            case sf::Event::MouseButtonReleased: {
                auto mousePos = sf::Vector2f((float) event.mouseButton.x, (float) event.mouseButton.y);
                if (this->_exitButton.getGlobalBounds().contains(sf::Vector2f(mousePos))) {
                    this->_data->window.close();
                }
                if (this->_mainMenuButton.getGlobalBounds().contains(sf::Vector2f(mousePos))) {
                    this->_data->manager.AddState(StateRef(new MainMenuState(this->_data)), true);
                }
            }
        }
    }
}

void LeaderboardState::Update() {}

void LeaderboardState::Draw()
{
    this->_data->window.clear(sf::Color::Red);

    this->_data->window.draw(this->_background);
    this->_data->window.draw(this->_mainMenuButton);
    this->_data->window.draw(this->_exitButton);

    this->_data->window.draw(this->_textBgEasy);
    this->_data->window.draw(this->_bannerEasy);
    this->_data->window.draw(this->_textEasyName);
    this->_data->window.draw(this->_textEasyTime);

    this->_data->window.draw(this->_textBgNormal);
    this->_data->window.draw(this->_bannerNormal);
    this->_data->window.draw(this->_textNormalName);
    this->_data->window.draw(this->_textNormalTime);

    this->_data->window.draw(this->_textBgHard);
    this->_data->window.draw(this->_bannerHard);
    this->_data->window.draw(this->_textHardName);
    this->_data->window.draw(this->_textHardTime);

    this->_data->window.display();
}