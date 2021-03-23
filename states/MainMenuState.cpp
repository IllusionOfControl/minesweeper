#include "MainMenuState.h"
#include "GameState.h"

MainMenuState::MainMenuState(GameDataRef data) : _data(data)
{

}

void MainMenuState::Init()
{
    this->_data->window.create(sf::VideoMode((WIDTH + GAME_BORDER_RIGHT + GAME_BORDER_LEFT) * SQUARE_SIZE,
                                             (HEIGHT + GAME_BORDER_TOP + GAME_BORDER_BOTTOM) * SQUARE_SIZE),
                               "Minesweeper");
    auto& backgroundTexture = this->_data->assets.GetTexture("background");
    auto windowSize = this->_data->window.getSize();

    backgroundTexture.setRepeated(true);
    this->_background.setTexture(backgroundTexture);
    this->_background.setTextureRect({0, 0, (int) windowSize.x, (int) windowSize.y});

    auto& buttonTextures = this->_data->assets.GetTexture(TEXTURE_SECOND_NAME);
    this->_playButton.setTexture(buttonTextures);
    this->_playButton.setTextureRect(BUTTON_INT_RECT(0, 32));


    this->_playButton.setPosition(GAME_BORDER_RIGHT * SQUARE_SIZE, GAME_BORDER_TOP * SQUARE_SIZE);

    auto& font = this->_data->assets.GetFont("default_font");

    this->_optionButton.setFont(font);
    this->_optionButton.setString("Options");
    this->_optionButton.setPosition(this->_data->window.getDefaultView().getSize().x / 2 - SQUARE_SIZE + 8, SQUARE_SIZE - 6);

    this->_exitButton.setFont(font);
    this->_exitButton.setString("Exit");
    this->_exitButton.setPosition(this->_data->window.getDefaultView().getSize().x / 2 - SQUARE_SIZE + 3, 8 * SQUARE_SIZE - 6);

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
            case sf::Event::MouseMoved:
                if (_playButton.getGlobalBounds().contains(event.mouseMove.x, event.mouseMove.y))
                    _playButton.setColor(sf::Color::Red);
                else _playButton.setColor(sf::Color::White);
                break;
            case sf::Event::MouseButtonPressed:
                if (this->_data->input.IsSpriteClicked(this->_playButton, this->_data->window))
                {
                    // Switch To Game State
                    this->_data->manager.AddState(StateRef(new GameState(_data)), true);
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
    this->_data->window.draw(this->_optionButton);
    this->_data->window.draw(this->_exitButton);
    this->_data->window.draw(this->_logo);

    this->_data->window.display();
}