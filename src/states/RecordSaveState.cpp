#include "RecordSaveState.hpp"


RecordSaveState::RecordSaveState(GameDataRef data) : _data(data) {

}

void RecordSaveState::Init() {
    this->_data->window.create(sf::VideoMode((WIDTH + GAME_BORDER_RIGHT + GAME_BORDER_LEFT + 1) * SQUARE_SIZE,
                                             (HEIGHT + GAME_BORDER_TOP + GAME_BORDER_BOTTOM) * SQUARE_SIZE),
                               "New RECORD!!!",
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
    this->_exitButton.setPosition((WIDTH + GAME_BORDER_RIGHT + 1) * SQUARE_SIZE, 0);

    auto &textBackground = this->_data->assets.GetTexture("text_background");
    textBackground.setRepeated(true);
    this->_nameTextBg.setTexture(textBackground);
    this->_nameTextBg.setTextureRect({0, 0, SQUARE_SIZE * 6, SQUARE_SIZE});
    this->_nameTextBg.setPosition(GAME_BORDER_RIGHT * SQUARE_SIZE, (GAME_BORDER_TOP - 1) * SQUARE_SIZE);
    this->_timeTextBg.setTexture(textBackground);
    this->_timeTextBg.setTextureRect({0, 0, SQUARE_SIZE * 6, SQUARE_SIZE});
    this->_timeTextBg.setPosition(GAME_BORDER_RIGHT * SQUARE_SIZE, (GAME_BORDER_TOP + 2) * SQUARE_SIZE);

    this->_nameLogo.setTexture(this->_data->assets.GetTexture(TEXTURE_SECOND_NAME));
    this->_nameLogo.setTextureRect({5 * SQUARE_SIZE * 5, 1 * SQUARE_SIZE, 192, 32});
    this->_nameLogo.setPosition(GAME_BORDER_RIGHT * SQUARE_SIZE, (GAME_BORDER_TOP - 2) * SQUARE_SIZE);
    this->_timeLogo.setTexture(this->_data->assets.GetTexture(TEXTURE_SECOND_NAME));
    this->_timeLogo.setTextureRect({5 * SQUARE_SIZE * 5, 2 * SQUARE_SIZE, 192, 32});
    this->_timeLogo.setPosition(GAME_BORDER_RIGHT * SQUARE_SIZE, (GAME_BORDER_TOP + 1) * SQUARE_SIZE);

    this->_nameInputText.setFont(this->_data->assets.GetFont("default_font"));
    this->_nameInputText.setCharacterSize(32);
    this->_nameInputText.setStyle(sf::Text::Bold);
    this->_nameInputText.setPosition(GAME_BORDER_RIGHT * SQUARE_SIZE + 5, (GAME_BORDER_TOP - 1) * SQUARE_SIZE - 10);
    this->_timeText.setFont(this->_data->assets.GetFont("default_font"));
    this->_timeText.setCharacterSize(32);
    this->_timeText.setStyle(sf::Text::Bold);
    this->_timeText.setPosition(GAME_BORDER_RIGHT * SQUARE_SIZE + 5, (GAME_BORDER_TOP + 2) * SQUARE_SIZE - 10);

    this->_saveButton.setTexture(this->_data->assets.GetTexture(TEXTURE_SECOND_NAME));
    this->_saveButton.setTextureRect({5 * SQUARE_SIZE * 5, 3 * SQUARE_SIZE, 192, 32});
    this->_saveButton.setPosition(GAME_BORDER_RIGHT * SQUARE_SIZE, (GAME_BORDER_TOP + 5) * SQUARE_SIZE);

    std::ostringstream time;
    time << this->_data->lastResults.time;
    _timeText.setString(time.str());
}

void RecordSaveState::HandleInput() {
    sf::Event event;

    while (this->_data->window.pollEvent(event)) {
        auto mousePos = sf::Vector2f((float) event.mouseMove.x, (float) event.mouseMove.y);
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

                if (this->_saveButton.getGlobalBounds().contains(sf::Vector2f(mousePos)))
                    this->_saveButton.setTextureRect({SQUARE_SIZE * 5 * 5, 4 * SQUARE_SIZE, SQUARE_SIZE * 6, SQUARE_SIZE});
                else this->_saveButton.setTextureRect({SQUARE_SIZE * 5 * 5, 3 * SQUARE_SIZE, SQUARE_SIZE * 6, SQUARE_SIZE});

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
                if (this->_saveButton.getGlobalBounds().contains(sf::Vector2f(mousePos))) {
                    if (_data->lastResults.name.empty()) _data->lastResults.name = "anon";
                    this->_data->leaderboard.SaveResult(_data->lastResults);
                    this->_data->manager.AddState(StateRef(new LeaderboardState(this->_data)), true);
                }
            }
            case sf::Event::TextEntered: {
                auto mousePos = sf::Vector2f(sf::Mouse::getPosition(this->_data->window));
                if (this->_nameInputText.getGlobalBounds().contains(mousePos) ||
                    this->_nameTextBg.getGlobalBounds().contains(mousePos)) {
                    if (event.text.unicode == '\b' && this->_nameStr.getSize() > 0)
                        this->_nameStr.erase(_nameStr.getSize() - 1, 1);
                    else if (((event.text.unicode >= 0x30 && event.text.unicode <= 0x39) ||
                              (event.text.unicode >= 0x41 && event.text.unicode <= 0x5A) ||
                              (event.text.unicode >= 0x61 && event.text.unicode <= 0x7A)) &&
                             _nameStr.getSize() < 9)
                        _nameStr += event.text.unicode;
                    _nameInputText.setString(_nameStr);
                    this->_data->lastResults.name = _nameStr;
                }
            }
        }
    }
}

void RecordSaveState::Update() {}

void RecordSaveState::Draw() {
    this->_data->window.clear(sf::Color::Red);

    this->_data->window.draw(this->_background);
    this->_data->window.draw(this->_mainMenuButton);
    this->_data->window.draw(this->_exitButton);

    this->_data->window.draw(this->_nameTextBg);
    this->_data->window.draw(this->_nameInputText);
    this->_data->window.draw(this->_nameLogo);
    this->_data->window.draw(this->_timeTextBg);
    this->_data->window.draw(this->_timeText);
    this->_data->window.draw(this->_timeLogo);
    this->_data->window.draw(this->_saveButton);

    this->_data->window.display();
}