#include "MineSweeper.h"
#include "states/MainMenuState.h"

MineSweeper::MineSweeper()
{
    _data->window.create(sf::VideoMode(200, 300), "MineSweeper", sf::Style::Close | sf::Style::Titlebar);
    _data->machine.AddState(StateRef(new MainMenuState(this->_data)));

    this->Run();
}

void MineSweeper::Run()
{
    while (this->_data->window.isOpen()) {
        this->_data->machine.ProcessStateChanges();
        this->_data->machine.GetActiveState()->HandleInput();
        this->_data->machine.GetActiveState()->Update();

        this->_data->machine.GetActiveState()->Draw();
    }
}