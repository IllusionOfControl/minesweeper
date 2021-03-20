#ifndef MINESWEEPER_DEFINITIONS_H
#define MINESWEEPER_DEFINITIONS_H

#define SCREEN_WIDTH 768
#define SCREEN_HEIGHT 1136

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
