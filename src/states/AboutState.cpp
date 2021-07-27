#include "AboutState.h"


AboutState::AboutState(GameDataRef data): _data(data)
{

}

void AboutState::Init()
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

    this->_mainMenuButton.setTexture(this->_data->assets.GetTexture("state_buttons"));
    this->_mainMenuButton.setTextureRect({0, 0, SQUARE_SIZE, SQUARE_SIZE});
    this->_mainMenuButton.setPosition(0 * SQUARE_SIZE, 0 * SQUARE_SIZE);

    this->_exitButton.setTexture(this->_data->assets.GetTexture("state_buttons"));
    this->_exitButton.setTextureRect({SQUARE_SIZE * 2, 0, SQUARE_SIZE, SQUARE_SIZE});
    this->_exitButton.setPosition((WIDTH + GAME_BORDER_RIGHT) * SQUARE_SIZE, 0);

    auto& authorButtonTextures = this->_data->assets.GetTexture(TEXTURE_SECOND_NAME);
    this->_authorButton.setTextureRect({0 * SQUARE_SIZE, 3 * SQUARE_SIZE, 160, 64});
    this->_authorButton.setTexture(authorButtonTextures);
    this->_authorButton.setPosition(GAME_BORDER_RIGHT * SQUARE_SIZE, GAME_BORDER_TOP * SQUARE_SIZE);

    this->_logo.setTexture(this->_data->assets.GetTexture(TEXTURE_SECOND_NAME));
    this->_logo.setTextureRect({0 * SQUARE_SIZE, 1 * SQUARE_SIZE, 160, 32});
    this->_logo.setPosition(GAME_BORDER_RIGHT * SQUARE_SIZE, 1 * SQUARE_SIZE);
}

void AboutState::HandleInput() {
    sf::Event event;

    while (this->_data->window.pollEvent(event))
    {
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

                if (this->_authorButton.getGlobalBounds().contains(mousePos))
                    this->_authorButton.setTextureRect({0 * SQUARE_SIZE, 3 * SQUARE_SIZE, 160, 64});
                else this->_authorButton.setTextureRect({5 * SQUARE_SIZE, 3 * SQUARE_SIZE, 160, 64});

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

void AboutState::Update()
{

}

void AboutState::Draw()
{
    this->_data->window.clear(sf::Color::Red);

    this->_data->window.draw(this->_background);
    this->_data->window.draw(this->_exitButton);
    this->_data->window.draw(this->_mainMenuButton);
    this->_data->window.draw(this->_authorButton);
    this->_data->window.draw(this->_logo);

    this->_data->window.display();
}