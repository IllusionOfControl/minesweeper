#include "MainMenuState.h"
#include "GameState.h"
#include "../DEFINITIONS.h"

MainMenuState::MainMenuState(GameDataRef data) : _data(data)
{

}

void MainMenuState::Init()
{
    this->_data->window.create(sf::VideoMode(MAIN_MENU_WIDTH, MAIN_MENU_HEIGHT), "MineSweeper", sf::Style::Close | sf::Style::Titlebar);
    this->_data->assets.LoadTexture("tile_block", GAME_FIELD_TILES, TILE_BLOCK);
    this->_data->assets.LoadTexture("Play Button", MAIN_MENU_PLAY_BUTTON);
    this->_data->assets.LoadTexture("Play Button Outer", MAIN_MENU_PLAY_BUTTON_OUTER);
    this->_data->assets.LoadTexture("Game logo", MAIN_MENU_LOGO_FILEPATH);

    auto& backgroundTexture = this->_data->assets.GetTexture("tile_block");
    backgroundTexture.setRepeated(true);
    this->_background.setTexture(backgroundTexture);
    this->_background.setTextureRect({0,0,MAIN_MENU_WIDTH, MAIN_MENU_HEIGHT});
    this->_playButton.setTexture(this->_data->assets.GetTexture("Play Button"));

    this->_logo.setTexture(this->_data->assets.GetTexture("Game logo"));

    this->_playButton.setPosition((32 * 1), (32 * 4));
    this->_logo.setPosition(32, 0);
}

void MainMenuState::HandleInput()
{
    sf::Event event;

    while (this->_data->window.pollEvent(event))
    {
        if (sf::Event::Closed == event.type) {
            this->_data->window.close();
        }

        if (event.type == sf::Event::MouseMoved) {
            if (_playButton.getGlobalBounds().contains(event.mouseMove.x, event.mouseMove.y))
                _playButton.setColor(sf::Color(0,255,0));
            else _playButton.setColor(sf::Color(255,255,255));
        }

        if (this->_data->input.IsSpriteClicked(this->_playButton, sf::Mouse::Left, this->_data->window))
        {
            // Switch To Game State
            this->_data->manager.AddState(StateRef(new GameState(_data)), true);
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
    this->_data->window.draw(this->_playButtonOuter);
    this->_data->window.draw(this->_logo);

    this->_data->window.display();
}