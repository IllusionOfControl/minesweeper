#include "MainMenuState.h"


MainMenuState::MainMenuState(GameDataRef data) : _data(data)
{

}

void MainMenuState::Init()
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

    auto& buttonTextures = this->_data->assets.GetTexture(TEXTURE_SECOND_NAME);
    this->_playButton.setTexture(buttonTextures);
    this->_playButton.setTextureRect(BUTTON_INT_RECT(0, 0));
    this->_aboutButton.setTexture(buttonTextures);
    this->_aboutButton.setTextureRect(BUTTON_INT_RECT(0, 1));
    this->_leaderboardsButton.setTexture(buttonTextures);
    this->_leaderboardsButton.setTextureRect(BUTTON_INT_RECT(5, 0));
    this->_exitButton.setTexture(buttonTextures);
    this->_exitButton.setTextureRect(BUTTON_INT_RECT(0, 2));

    this->_playButton.setPosition(GAME_BORDER_RIGHT * SQUARE_SIZE, GAME_BORDER_TOP * SQUARE_SIZE);
    this->_aboutButton.setPosition(GAME_BORDER_RIGHT * SQUARE_SIZE, (GAME_BORDER_TOP + 2) * SQUARE_SIZE);
    this->_leaderboardsButton.setPosition(GAME_BORDER_RIGHT * SQUARE_SIZE, (GAME_BORDER_TOP + 4) * SQUARE_SIZE);
    this->_exitButton.setPosition(GAME_BORDER_RIGHT * SQUARE_SIZE, (GAME_BORDER_TOP + 6) * SQUARE_SIZE);

    this->_logo.setTexture(this->_data->assets.GetTexture("logo"));
    this->_logo.setPosition(32, 0);
}

void MainMenuState::HandleInput()
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
                if (this->_playButton.getGlobalBounds().contains(mousePos))
                    this->_playButton.setColor(sf::Color::Red);
                else
                    this->_playButton.setColor(sf::Color::White);
                if (this->_aboutButton.getGlobalBounds().contains(mousePos))
                    this->_aboutButton.setColor(sf::Color::Red);
                else
                    this->_aboutButton.setColor(sf::Color::White);
                if (this->_leaderboardsButton.getGlobalBounds().contains(mousePos))
                    this->_leaderboardsButton.setColor(sf::Color::Red);
                else
                    this->_leaderboardsButton.setColor(sf::Color::White);
                if (this->_exitButton.getGlobalBounds().contains(mousePos))
                    this->_exitButton.setColor(sf::Color::Red);
                else
                    this->_exitButton.setColor(sf::Color::White);
                break;
            }
            case sf::Event::MouseButtonReleased: {
                auto mousePos = sf::Vector2f((float) event.mouseButton.x, (float) event.mouseButton.y);
                if (this->_playButton.getGlobalBounds().contains(mousePos))
                    this->_data->manager.AddState(StateRef(new DifficultyMenuState(_data)), true);
                if (this->_aboutButton.getGlobalBounds().contains(mousePos))
                    this->_data->manager.AddState(StateRef(new AboutState(_data)), true);
                if (this->_leaderboardsButton.getGlobalBounds().contains(mousePos))
                    this->_data->manager.AddState(StateRef(new LeaderboardState(_data)), true);
                if (this->_exitButton.getGlobalBounds().contains(mousePos)) {
                    this->_data->window.close();
                }
            }
        }
    }
}

void MainMenuState::Update()
{

}

void MainMenuState::Draw()
{
    this->_data->window.clear(sf::Color::Red);

    this->_data->window.draw(this->_background);
    this->_data->window.draw(this->_playButton);
    this->_data->window.draw(this->_aboutButton);
    this->_data->window.draw(this->_leaderboardsButton);
    this->_data->window.draw(this->_exitButton);
    this->_data->window.draw(this->_logo);

    this->_data->window.display();
}