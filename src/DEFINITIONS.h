#ifndef MINESWEEPER_DEFINITIONS_H
#define MINESWEEPER_DEFINITIONS_H

// Field layout, measured in cells.
constexpr int GAME_BORDER_TOP = 4;
constexpr int GAME_BORDER_BOTTOM = 1;
constexpr int GAME_BORDER_RIGHT = 1;
constexpr int GAME_BORDER_LEFT = 1;
constexpr int WIDTH = 5;
constexpr int HEIGHT = 7;

constexpr int SQUARE_SIZE = 32;

inline constexpr const char *TEXTURE_SECOND_NAME = "second";

// Sub-rectangles into the sprite sheets, expressed as sf::IntRect initializers.
#define BUTTON_INT_RECT(pos_x, pos_y)       {pos_x * SQUARE_SIZE * 5, pos_y * SQUARE_SIZE, 160, 32}
#define TILE_INT_RECT(tile_type)            {tile_type * 32, 0, 32, 32}

#endif //MINESWEEPER_DEFINITIONS_H
