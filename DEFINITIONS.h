#ifndef MINESWEEPER_DEFINITIONS_H
#define MINESWEEPER_DEFINITIONS_H

#define MAIN_MENU_WIDTH 224
#define MAIN_MENU_HEIGHT 320

#define TILE_WIDTH  32
#define TILE_HEIGHT 32

#define BUTTON_WIDTH  32
#define BUTTON_HEIGHT 512

#define SMALL_BUTTON_WIDTH  32
#define SMALL_BUTTON_HEIGHT 32

#define TILE_0              {0, TILE_HEIGHT * 0, TILE_WIDTH, TILE_HEIGHT}
#define TILE_1              {0, TILE_HEIGHT * 1, TILE_WIDTH, TILE_HEIGHT}
#define TILE_2              {0, TILE_HEIGHT * 2, TILE_WIDTH, TILE_HEIGHT}
#define TILE_3              {0, TILE_HEIGHT * 3, TILE_WIDTH, TILE_HEIGHT}
#define TILE_4              {0, TILE_HEIGHT * 4, TILE_WIDTH, TILE_HEIGHT}
#define TILE_5              {0, TILE_HEIGHT * 5, TILE_WIDTH, TILE_HEIGHT}
#define TILE_6              {0, TILE_HEIGHT * 6, TILE_WIDTH, TILE_HEIGHT}
#define TILE_7              {0, TILE_HEIGHT * 7, TILE_WIDTH, TILE_HEIGHT}
#define TILE_8              {0, TILE_HEIGHT * 8, TILE_WIDTH, TILE_HEIGHT}
#define TILE_BOMB           {0, TILE_HEIGHT * 9, TILE_WIDTH, TILE_HEIGHT}
#define TILE_BOMB_DETONATED {0, TILE_HEIGHT * 10, TILE_WIDTH, TILE_HEIGHT}
#define TILE_BOMB_FALSE     {0, TILE_HEIGHT * 11, TILE_WIDTH, TILE_HEIGHT}
#define TILE_FLAG           {0, TILE_HEIGHT * 12, TILE_WIDTH, TILE_HEIGHT}
#define TILE_QUESTION       {0, TILE_HEIGHT * 13, TILE_WIDTH, TILE_HEIGHT}
#define TILE_BLOCK          {0, TILE_HEIGHT * 14, TILE_WIDTH, TILE_HEIGHT}
#define TILE_EMPTY          {0, TILE_HEIGHT * 15, TILE_WIDTH, TILE_HEIGHT}

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

#define STATE_PLAYING   0
#define STATE_WON       1
#define STATE_LOSE      2

#define TIME_BEFORE_SHOWING_GAME_OVER 3

#endif //MINESWEEPER_DEFINITIONS_H
