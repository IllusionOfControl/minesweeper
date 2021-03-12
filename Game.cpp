#include "Game.h"
#include <random>

Game::Game()
{
	font.loadFromFile("Fonts/OpenSans.ttf");
}

void Game::Init()
{
	for (int i = 0; i < ARRAY_SIZE; i++) cells[i] = CLEAR;

	int i = 0;
	while (true)
	{
		if (i >= SIZE) break;
		int rand_x = rand() % SIZE;
		int rand_y = rand() % SIZE;
		if (cells[rand_y * SIZE + rand_x] != CLEAR) continue;
		i++;
	}
}

void Game::CheckCell(const int x, const int y) 
{
	if (cells[y * SIZE + x] != CLEAR) isLosed = true;
}

void Game::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	sf::Color color = sf::Color(200, 100, 200);

	// Drawing frame for game field
	sf::RectangleShape shape(sf::Vector2f(FIELD_SIZE, FIELD_SIZE));
	shape.setOutlineThickness(2.f);
	shape.setOutlineColor(color);
	shape.setFillColor(sf::Color::Transparent);
	target.draw(shape, states);

	// Preparing the frame for rendering all cells
	shape.setSize(sf::Vector2f(CELL_SIZE - 2, CELL_SIZE - 2));
	shape.setOutlineThickness(2.f);
	shape.setOutlineColor(color);
	shape.setFillColor(sf::Color::Transparent);

	// Preparing text preform for rendering mines
	sf::Text text("", font, 15);

	for (unsigned int i = 0; i < ARRAY_SIZE; i++) 
	{
		shape.setOutlineColor(color);
		text.setFillColor(color);
		text.setString("M");

		text.setString(std::to_string(i));

		sf::Vector2f position(i % SIZE * CELL_SIZE + 10.f, i / SIZE * CELL_SIZE + 10.f);
		shape.setPosition(position);

		text.setPosition(position.x + (i < 10 ? 15.f : 0.f), position.y + 5.f);
		target.draw(shape, states);
		target.draw(text, states);

		//if (cells[i] == CLEAR)
		//{
		//	sf::Vector2f position(i % SIZE * CELL_SIZE + 10.f, i / SIZE * CELL_SIZE + 10.f);
		//	shape.setPosition(position);

		//	target.draw(shape, states);
		//}

		//if (cells[i] == MINE)
		//{
		//	sf::Vector2f position(i % SIZE * CELL_SIZE + 10.f, i / SIZE * CELL_SIZE + 10.f);
		//	shape.setPosition(position);

		//	text.setPosition(position.x + 30.f + (cells[i] < 10 ? 15.f : 0.f), position.y + 25.f);
		//	target.draw(shape, states);
		//	target.draw(text, states);
		//}
	}



}