#include "Game.h"
#include <iostream>

Game::Game()
{
	font.loadFromFile("Fonts/OpenSans.ttf");
}

void printVector(sf::Vector2f pos) {
    std::cout << pos.y << " " << pos.x << std::endl;
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
		cells[rand_y * SIZE + rand_x] = MINE;
		i++;
	}
	cells[1]=MINE;
}

void Game::event(sf::Event e) {
    if (e.type == sf::Event::MouseButtonReleased) {
        sf::Vector2f mousePosition = sf::Vector2f(e.mouseButton.x, e.mouseButton.y);
        mousePos = mousePosition;
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

	for (unsigned int i = 0; i < ARRAY_SIZE; i++) {
        shape.setOutlineColor(color);
        text.setFillColor(color);
        text.setString("M");

        //text.setString(std::to_string(cells[i]));

        //sf::Vector2f position(i % SIZE * CELL_SIZE + 10.f, i / SIZE * CELL_SIZE + 10.f);
        //shape.setPosition(position);

        //text.setPosition(position.x + (cells[i] < 10 ? 15.f : 0.f), position.y + 5.f);
        //target.draw(shape, states);
        //target.draw(text, states);

        if (cells[i] == CLEAR) {
            sf::Vector2f position(i % SIZE * CELL_SIZE + 10.f, i / SIZE * CELL_SIZE + 10.f);
            shape.setPosition(position);

            target.draw(shape, states);
        }

        if (cells[i] == MINE) {
            sf::Vector2f position(i % SIZE * CELL_SIZE + 10.f, i / SIZE * CELL_SIZE + 10.f);
            shape.setPosition(position);

            if (shape.getGlobalBounds().contains(mousePos - this->getPosition())) {
                shape.setFillColor(sf::Color(200, 100, 200));
            }

            text.setPosition(position.x + 5.f, position.y + 5.f);
            target.draw(shape, states);
            target.draw(text, states);
            shape.setFillColor(sf::Color(0,0,0));
        }
        // this->getPos

        //printVector(this->getPosition());
    }
}