#include <SFML/Graphics.hpp>
#include "Game.h"
#include <iostream>

int main()
{
	sf::RenderWindow window(sf::VideoMode(600, 600), "MineSweeper");
	window.setFramerateLimit(60);

	sf::Event event;

	sf::Font font;
	font.loadFromFile("Fonts/OpenSans.ttf");

	sf::Text text("Esc - Exit / F2 - New Game", font, 20);
	text.setFillColor(sf::Color::Cyan);
	text.setPosition(5.f, 5.f);

	Game game;
	game.setPosition(50.f, 50.f);
	game.Init();

	while (window.isOpen()) 
	{
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) window.close();
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Escape) window.close();
				if (event.key.code == sf::Keyboard::F2) game.Init();
			}
			if (event.type == sf::Event::MouseButtonReleased) {
                game.event(event);
			}
			if (event.type == sf::Event::MouseMoved) {
			    std::cout << event.mouseMove.x << " " << event.mouseMove.y << std::endl;
			}
		}
		window.clear();
		window.draw(game);
		window.draw(text);
		window.display();
	}
	return 0;
}