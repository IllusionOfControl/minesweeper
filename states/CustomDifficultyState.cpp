#include <sstream>
#include "CustomDifficultyState.h"

#include "iostream"

CustomDifficultyState::CustomDifficultyState(GameDataRef data) : _data(data) {

}

void CustomDifficultyState::Init() {
    this->_data->window.create(sf::VideoMode((WIDTH + GAME_BORDER_RIGHT + GAME_BORDER_LEFT) * SQUARE_SIZE,
                                             (HEIGHT + GAME_BORDER_TOP + GAME_BORDER_BOTTOM) * SQUARE_SIZE),
                               "Minesweeper",
                               sf::Style::Titlebar | sf::Style::Close);
    auto& backgroundTexture = this->_data->assets.GetTexture("background");
    auto windowSize = this->_data->window.getSize();

    backgroundTexture.setRepeated(true);
    this->_background.setTexture(backgroundTexture);
    this->_background.setTextureRect({0, 0, (int) windowSize.x, (int) windowSize.y});

    this->_mainMenuButton.setTexture(this->_data->assets.GetTexture("state_buttons"));
    this->_mainMenuButton.setTextureRect({0, 0, SQUARE_SIZE, SQUARE_SIZE});
    this->_mainMenuButton.setPosition(0 * SQUARE_SIZE, 0 * SQUARE_SIZE);

    this->_exitButton.setTexture(this->_data->assets.GetTexture("state_buttons"));
    this->_exitButton.setTextureRect({SQUARE_SIZE * 2, 0, SQUARE_SIZE, SQUARE_SIZE});
    this->_exitButton.setPosition((WIDTH + GAME_BORDER_RIGHT) * SQUARE_SIZE, 0);

    auto& textBackground = this->_data->assets.GetTexture("text_background");
    textBackground.setRepeated(true);
    this->_widthTextBackground.setTexture(textBackground);
    this->_widthTextBackground.setTextureRect({0, 0, SQUARE_SIZE * 5, SQUARE_SIZE});
    this->_widthTextBackground.setPosition(GAME_BORDER_RIGHT * SQUARE_SIZE, (GAME_BORDER_TOP - 1) * SQUARE_SIZE);
    this->_heightTextBackground.setTexture(textBackground);
    this->_heightTextBackground.setTextureRect({0, 0, SQUARE_SIZE * 5, SQUARE_SIZE});
    this->_heightTextBackground.setPosition(GAME_BORDER_RIGHT * SQUARE_SIZE, (GAME_BORDER_TOP +1) * SQUARE_SIZE);
    this->_minesTextBackground.setTexture(textBackground);
    this->_minesTextBackground.setTextureRect({0, 0, SQUARE_SIZE * 5, SQUARE_SIZE});
    this->_minesTextBackground.setPosition(GAME_BORDER_RIGHT * SQUARE_SIZE, (GAME_BORDER_TOP + 3) * SQUARE_SIZE);

    this->_widthText.setFont(this->_data->assets.GetFont("default_font"));
    this->_widthText.setCharacterSize(32);
    this->_widthText.setStyle(sf::Text::Bold);
    this->_widthText.setPosition(GAME_BORDER_RIGHT * SQUARE_SIZE + 20, (GAME_BORDER_TOP - 1) * SQUARE_SIZE - 10);
    this->_heightText.setFont(this->_data->assets.GetFont("default_font"));
    this->_heightText.setCharacterSize(32);
    this->_heightText.setStyle(sf::Text::Bold);
    this->_heightText.setPosition(GAME_BORDER_RIGHT * SQUARE_SIZE + 20, (GAME_BORDER_TOP + 1) * SQUARE_SIZE - 10);
    this->_minesText.setFont(this->_data->assets.GetFont("default_font"));
    this->_minesText.setCharacterSize(32);
    this->_minesText.setStyle(sf::Text::Bold);
    this->_minesText.setPosition(GAME_BORDER_RIGHT * SQUARE_SIZE + 20, (GAME_BORDER_TOP + 3) * SQUARE_SIZE - 10);

    this->_widthLogo.setTexture(this->_data->assets.GetTexture(TEXTURE_SECOND_NAME));
    this->_widthLogo.setTextureRect(BUTTON_INT_RECT(1, 2));
    this->_widthLogo.setPosition(GAME_BORDER_RIGHT * SQUARE_SIZE, (GAME_BORDER_TOP - 2) * SQUARE_SIZE);
    this->_heightLogo.setTexture(this->_data->assets.GetTexture(TEXTURE_SECOND_NAME));
    this->_heightLogo.setTextureRect(BUTTON_INT_RECT(3, 2));
    this->_heightLogo.setPosition(GAME_BORDER_RIGHT * SQUARE_SIZE, (GAME_BORDER_TOP) * SQUARE_SIZE);
    this->_minesLogo.setTexture(this->_data->assets.GetTexture(TEXTURE_SECOND_NAME));
    this->_minesLogo.setTextureRect(BUTTON_INT_RECT(3, 3));
    this->_minesLogo.setPosition(GAME_BORDER_RIGHT * SQUARE_SIZE, (GAME_BORDER_TOP + 2) * SQUARE_SIZE);

    this->_playButton.setTexture(this->_data->assets.GetTexture(TEXTURE_SECOND_NAME));
    this->_playButton.setTextureRect(BUTTON_INT_RECT(3, 4));
    this->_playButton.setPosition(GAME_BORDER_RIGHT * SQUARE_SIZE, (GAME_BORDER_TOP + 4) * SQUARE_SIZE);

    this->isValidDifficulty = false;
}

void CustomDifficultyState::HandleInput() {
    sf::Event event;

    while (this->_data->window.pollEvent(event)) {
        auto mousePos = sf::Vector2f((float) event.mouseMove.x, (float) event.mouseMove.y);
        switch (event.type) {
            case sf::Event::Closed:
                this->_data->window.close();
                break;
            case sf::Event::MouseMoved: {

                if (this->_widthLogo.getGlobalBounds().contains(mousePos) ||
                    this->_widthTextBackground.getGlobalBounds().contains(mousePos))
                    this->_widthLogo.setTextureRect(BUTTON_INT_RECT(2, 2));
                else
                    this->_widthLogo.setTextureRect(BUTTON_INT_RECT(1, 2));
                if (this->_heightLogo.getGlobalBounds().contains(mousePos) ||
                    this->_heightTextBackground.getGlobalBounds().contains(mousePos))
                    this->_heightLogo.setTextureRect(BUTTON_INT_RECT(4, 2));
                else
                    this->_heightLogo.setTextureRect(BUTTON_INT_RECT(3, 2));
                if (this->_minesLogo.getGlobalBounds().contains(mousePos) ||
                    this->_minesTextBackground.getGlobalBounds().contains(mousePos))
                    this->_minesLogo.setTextureRect(BUTTON_INT_RECT(3, 3));
                else
                    this->_minesLogo.setTextureRect(BUTTON_INT_RECT(4, 3));
                if (this->_playButton.getGlobalBounds().contains(mousePos))
                    this->_playButton.setTextureRect(BUTTON_INT_RECT(4, 4));
                else
                    this->_playButton.setTextureRect(BUTTON_INT_RECT(3, 4));
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
                if (this->_playButton.getGlobalBounds().contains(mousePos)) {
                    if (this->isValidDifficulty)
                        this->_data->difficulty.difficulty_type = GAME_CUSTOM;
                        this->_data->manager.AddState(StateRef(new GameState(_data)), true);
                }
                if (this->_exitButton.getGlobalBounds().contains(sf::Vector2f(mousePos))) {
                    this->_data->window.close();
                }
                if (this->_mainMenuButton.getGlobalBounds().contains(sf::Vector2f(mousePos))) {
                    this->_data->manager.AddState(StateRef(new MainMenuState(this->_data)), true);
                }
            }
            case sf::Event::TextEntered: {
                auto mousePos = sf::Vector2f(sf::Mouse::getPosition(this->_data->window));
                if (this->_widthLogo.getGlobalBounds().contains(mousePos) ||
                    this->_widthTextBackground.getGlobalBounds().contains(mousePos)) {
                    if (event.text.unicode == '\b' && this->_widthString.getSize() > 0)
                        this->_widthString.erase(_widthString.getSize() - 1, 1);
                    else if (event.text.unicode >= 0x30 && event.text.unicode <= 0x39)
                        _widthString += event.text.unicode;
                    _widthText.setString(_widthString);
                    std::stringstream convert(_widthString);
                    convert >> this->_data->difficulty.field_width;
                }
                if (this->_heightLogo.getGlobalBounds().contains(mousePos) ||
                    this->_heightTextBackground.getGlobalBounds().contains(mousePos)) {
                    if (event.text.unicode == '\b' && this->_heightString.getSize() > 0)
                        this->_heightString.erase(_heightString.getSize() - 1, 1);
                    else if (event.text.unicode >= 0x30 && event.text.unicode <= 0x39)
                        _heightString += event.text.unicode;
                    _heightText.setString(_heightString);
                    std::stringstream convert(_heightString);
                    convert >> this->_data->difficulty.field_height;
                }
                if (this->_minesLogo.getGlobalBounds().contains(mousePos) ||
                    this->_minesTextBackground.getGlobalBounds().contains(mousePos)) {
                    if (event.text.unicode == '\b' && this->_minesString.getSize() > 0)
                        this->_minesString.erase(_minesString.getSize() - 1, 1);
                    else if (event.text.unicode >= 0x30 && event.text.unicode <= 0x39)
                        _minesString += event.text.unicode;
                    _minesText.setString(_minesString);
                    std::stringstream convert(_minesString);
                    convert >> this->_data->difficulty.bomb_count;
                }
            }
        }
    }
}

void CustomDifficultyState::Update() {
    if (this->_data->difficulty.field_width >= 5 &&
        this->_data->difficulty.field_width <= 18)
        this->_widthText.setFillColor(sf::Color::Green);
    else
        this->_widthText.setFillColor(sf::Color::Red);

    if (this->_data->difficulty.field_height >= 5 &&
        this->_data->difficulty.field_height <= 18)
        this->_heightText.setFillColor(sf::Color::Green);
    else
        this->_heightText.setFillColor(sf::Color::Red);

    if (this->_data->difficulty.bomb_count >= 5 &&
        this->_data->difficulty.bomb_count <= 320 &&
        this->_data->difficulty.field_height * this->_data->difficulty.field_width > this->_data->difficulty.bomb_count)
        this->_minesText.setFillColor(sf::Color::Green);
    else
        this->_minesText.setFillColor(sf::Color::Red);

    this->isValidDifficulty = false;
    if (this->_widthText.getFillColor() == sf::Color::Green &&
        this->_heightText.getFillColor() == sf::Color::Green &&
        this->_minesText.getFillColor() == sf::Color::Green)
        this->isValidDifficulty = true;
}

void CustomDifficultyState::Draw() {
    this->_data->window.clear(sf::Color::Red);

    this->_data->window.draw(this->_background);
    this->_data->window.draw(this->_widthTextBackground);
    this->_data->window.draw(this->_heightTextBackground);
    this->_data->window.draw(this->_minesTextBackground);
    this->_data->window.draw(this->_widthLogo);
    this->_data->window.draw(this->_heightLogo);
    this->_data->window.draw(this->_minesLogo);
    this->_data->window.draw(this->_widthText);
    this->_data->window.draw(this->_heightText);
    this->_data->window.draw(this->_minesText);

    this->_data->window.draw(this->_playButton);
    this->_data->window.draw(this->_exitButton);
    this->_data->window.draw(this->_mainMenuButton);

    this->_data->window.display();
}