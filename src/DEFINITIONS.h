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

#define BACKGROUND_INT_RECT                 {}
//#define BUTTON_INT_RECT(pos_x, pos_y)       {pos_x, pos_y, 160, 32}
#define BUTTON_INT_RECT(pos_x, pos_y)       {pos_x * SQUARE_SIZE * 5, pos_y * SQUARE_SIZE, 160, 32}
#define TILE_INT_RECT(tile_type)            {tile_type * 32, 0, 32, 32}
#define SMILE_SMALL_INT_RECT(pos_x)  {pos_x * SQUARE_SIZE, 0 * SQUARE_SIZE, SQUARE_SIZE, SQUARE_SIZE}
#define SMILE_LARGE_INT_RECT(pos_x)  {pos_x * SQUARE_SIZE * 2 + (SQUARE_SIZE * 5), 0 * SQUARE_SIZE, SQUARE_SIZE * 2, SQUARE_SIZE}

#define SMALL_BUTTON_WIDTH  32
#define SMALL_BUTTON_HEIGHT 32

#define CELL_EMPTY          0x0
#define CELL_0              0x0
#define CELL_1              0x1
#define CELL_2              0x2
#define CELL_3              0x3
#define CELL_4              0x4
#define CELL_5              0x5
#define CELL_6              0x6
#define CELL_7              0x7
#define CELL_8              0x8
#define CELL_BOMB           0x9
#define CELL_BOMB_DETONATED 0xA
#define CELL_BOMB_FALSE     0xB
#define CELL_FLAG           0x10
#define CELL_QUESTION       0x20
#define CELL_REVEALED       0x40
#define CELL_SELECTED       0x80

#define SMILE_USUAL     0
#define SMILE_REVEAL    1
#define SMILE_CLICK     2
#define SMILE_WIN       3
#define SMILE_LOSE      4

#define GAME_FIELD_TILES "_Resources/res/tiles.png"

#define MAIN_MENU_BACKGROUND_FILEPATH "_Resources/res/background.png"
#define GAME_BACKGROUND_FILEPATH "Resources/res/Main Menu Background.png"
#define PAUSE_BACKGROUND_FILEPATH "Resources/res/Main Menu Background.png"

#define MAIN_MENU_LOGO_FILEPATH "_Resources/res/logo.png"

#define MAIN_MENU_PLAY_BUTTON "_Resources/res/main_menu_game_button.png"
#define RESUME_BUTTON "Resources/res/Resume Button.png"
#define HOME_BUTTON "Resources/res/Home Button.png"
#define RETRY_BUTTON "Resources/res/Retry Button.png"

#define MAIN_MENU_PLAY_BUTTON_OUTER "_Resources/res/Play Button Outer.png"

#define PAUSE_BUTTON "_Resources/res/Pause Button.png"

#define X_PIECE_FILEPATH "_Resources/res/X.png"
#define O_PIECE_FILEPATH "_Resources/res/O.png"
#define X_WINNING_PIECE_FILEPATH "_Resources/res/X Win.png"
#define O_WINNING_PIECE_FILEPATH "_Resources/res/O Win.png"

#define GRID_SPRITE_FILEPATH "_Resources/res/Grid.png"

#define X_PIECE 8
#define O_PIECE 0
#define EMPTY_PIECE -1
#define PLAYER_PIECE X_PIECE
#define AI_PIECE O_PIECE

#define STATE_FIRST_MOVE   0
#define STATE_PLAYING   1
#define STATE_WON       2
#define STATE_LOSE      3

#define GAME_EASY   1
#define GAME_NORMAL 2
#define GAME_HARD   3
#define GAME_CUSTOM 4

#define DIFFICULTY_EASY     {9, 9, 10, GAME_EASY};
#define DIFFICULTY_MEDIUM   {16, 16, 40, GAME_NORMAL};
#define DIFFICULTY_HARD     {32, 16, 99, GAME_HARD};

#endif //MINESWEEPER_DEFINITIONS_H
