#ifndef MINESWEEPER_DEFINITIONS_H
#define MINESWEEPER_DEFINITIONS_H

// Definitions in squares
#define GAME_BORDER_TOP     4
#define GAME_BORDER_BOTTOM  1
#define GAME_BORDER_RIGHT   1
#define GAME_BORDER_LEFT    1
#define WIDTH   5
#define HEIGHT  7

#define SQUARE_SIZE 32

#define TEXTURE_SECOND_NAME "second"

#define BUTTON_INT_RECT(pos_x, pos_y)       {pos_x * SQUARE_SIZE * 5, pos_y * SQUARE_SIZE, 160, 32}
#define TILE_INT_RECT(tile_type)            {tile_type * 32, 0, 32, 32}

#define CELL_EMPTY          0x0
#define CELL_BOMB           0x9
#define CELL_BOMB_DETONATED 0xA
#define CELL_FLAG           0x10
#define CELL_QUESTION       0x20
#define CELL_REVEALED       0x40
#define CELL_SELECTED       0x80

#define GAME_EASY   1
#define GAME_NORMAL 2
#define GAME_HARD   3

#define DIFFICULTY_EASY     {9, 9, 10, GAME_EASY};
#define DIFFICULTY_MEDIUM   {16, 16, 40, GAME_NORMAL};
#define DIFFICULTY_HARD     {32, 16, 99, GAME_HARD};

#endif //MINESWEEPER_DEFINITIONS_H
