#include "DifficultyMenuState.h"

DifficultyMenuState::DifficultyMenuState(GameDataRef data) : _data(data)
{

}

void DifficultyMenuState::Init()
{
    this->_data->window.create(sf::VideoMode((WIDTH + GAME_BORDER_RIGHT + GAME_BORDER_LEFT) * SQUARE_SIZE,
                                             (HEIGHT + GAME_BORDER_TOP + GAME_BORDER_BOTTOM) * SQUARE_SIZE),
                               "Minesweeper",
                               sf::Style::Titlebar | sf::Style::Close);
    auto& backgroundTexture = this->_data->assets.GetTexture("background");
    auto windowSize = this->_data->window.getSize();

    backgroundTexture.setRepeated(true);
    this->_background.setTexture(backgroundTexture);
    this->_background.setTextureRect({0, 0, (int) windowSize.x, (int) windowSize.y});

    this->_easyButton.setTexture(this->_data->assets.GetTexture(TEXTURE_SECOND_NAME));
    this->_easyButton.setTextureRect(BUTTON_INT_RECT(1, 0));
    this->_easyButton.setPosition(GAME_BORDER_RIGHT * SQUARE_SIZE, (GAME_BORDER_TOP - 2) * SQUARE_SIZE);

    this->_mediumButton.setTexture(this->_data->assets.GetTexture(TEXTURE_SECOND_NAME));
    this->_mediumButton.setTextureRect(BUTTON_INT_RECT(3, 0));
    this->_mediumButton.setPosition(GAME_BORDER_RIGHT * SQUARE_SIZE, GAME_BORDER_TOP * SQUARE_SIZE);

    this->_hardButton.setTexture(this->_data->assets.GetTexture(TEXTURE_SECOND_NAME));
    this->_hardButton.setTextureRect(BUTTON_INT_RECT(1, 1));
    this->_hardButton.setPosition(GAME_BORDER_RIGHT * SQUARE_SIZE, (GAME_BORDER_TOP + 2) * SQUARE_SIZE);

    this->_customButton.setTexture(this->_data->assets.GetTexture(TEXTURE_SECOND_NAME));
    this->_customButton.setTextureRect(BUTTON_INT_RECT(3, 1));
    this->_customButton.setPosition(GAME_BORDER_RIGHT * SQUARE_SIZE, (GAME_BORDER_TOP + 4) * SQUARE_SIZE);

    this->_mainMenuButton.setTexture(this->_data->assets.GetTexture("state_buttons"));
    this->_mainMenuButton.setTextureRect({0, 0, SQUARE_SIZE, SQUARE_SIZE});
    this->_mainMenuButton.setPosition(0 * SQUARE_SIZE, 0 * SQUARE_SIZE);

    this->_exitButton.setTexture(this->_data->assets.GetTexture("state_buttons"));
    this->_exitButton.setTextureRect({SQUARE_SIZE * 2, 0, SQUARE_SIZE, SQUARE_SIZE});
    this->_exitButton.setPosition((WIDTH + GAME_BORDER_RIGHT) * SQUARE_SIZE, 0);
}

void DifficultyMenuState::HandleInput()
{
    sf::Event event;

    while (this->_data->window.pollEvent(event))
    {
        switch (event.type) {
            case sf::Event::Closed:
                this->_data->window.close();
                break;
            case sf::Event::MouseMoved: {
                auto mousePos = sf::Vector2f((float) event.mouseMove.x, (float) event.mouseMove.y);
                if (this->_easyButton.getGlobalBounds().contains(mousePos))
                    this->_easyButton.setTextureRect(BUTTON_INT_RECT(2, 0));
                else
                    this->_easyButton.setTextureRect(BUTTON_INT_RECT(1, 0));
                if (this->_mediumButton.getGlobalBounds().contains(mousePos))
                    this->_mediumButton.setTextureRect(BUTTON_INT_RECT(4, 0));
                else
                    this->_mediumButton.setTextureRect(BUTTON_INT_RECT(3, 0));
                if (this->_hardButton.getGlobalBounds().contains(mousePos))
                    this->_hardButton.setTextureRect(BUTTON_INT_RECT(2, 1));
                else
                    this->_hardButton.setTextureRect(BUTTON_INT_RECT(1, 1));
                if (this->_customButton.getGlobalBounds().contains(mousePos))
                    this->_customButton.setTextureRect(BUTTON_INT_RECT(4, 1));
                else
                    this->_customButton.setTextureRect(BUTTON_INT_RECT(3, 1));
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
                if (this->_easyButton.getGlobalBounds().contains(mousePos)) {
                    this->_data->difficulty = DIFFICULTY_EASY;
                    this->_data->manager.AddState(StateRef(new GameState(_data)), true);
                }
                if (this->_mediumButton.getGlobalBounds().contains(mousePos)) {
                    this->_data->difficulty = DIFFICULTY_MEDIUM;
                    this->_data->manager.AddState(StateRef(new GameState(_data)), true);
                }
                if (this->_hardButton.getGlobalBounds().contains(mousePos)) {
                    this->_data->difficulty = DIFFICULTY_HARD;
                    this->_data->manager.AddState(StateRef(new GameState(_data)), true);
                }
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


void DifficultyMenuState::Update()
{

}

void DifficultyMenuState::Draw()
{
    this->_data->window.clear(sf::Color::Red);

    this->_data->window.draw(this->_background);
    this->_data->window.draw(this->_easyButton);
    this->_data->window.draw(this->_mediumButton);
    this->_data->window.draw(this->_hardButton);
    this->_data->window.draw(this->_customButton);

    this->_data->window.draw(this->_exitButton);
    this->_data->window.draw(this->_mainMenuButton);

    this->_data->window.display();
}