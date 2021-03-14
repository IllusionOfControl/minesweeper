#pragma once

#include <SFML/Graphics.hpp>

const int SIZE = 16;
const int ARRAY_SIZE = SIZE * SIZE;
const int FIELD_SIZE = 500;
const int CELL_SIZE = 30;
const int MINES_COUNT = 10;

enum CELL_TYPE
{
	CLEAR,
	MINE
};

class Game : public sf::Drawable, public sf::Transformable
{
protected:
	int cells[ARRAY_SIZE];
	sf::Vector2f mousePos;
	bool isLosed;
	sf::Font font;
public:
	Game();
	void Init();
	void CheckCell(const int, const int);
	virtual void draw(sf::RenderTarget&, sf::RenderStates) const;

	void event(sf::Event);
};
