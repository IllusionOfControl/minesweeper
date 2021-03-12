#include <SFML/Graphics.hpp>
#include "Game.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(600, 600), "MineSweeper");
	window.setFramerateLimit(60);

	sf::Event event;

	sf::Font font;
	font.loadFromFile("Fonts/OpenSans.ttf");

	
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
			}
		}
		window.clear();
		window.draw(game);
		window.display();
	}
	return 0;
}