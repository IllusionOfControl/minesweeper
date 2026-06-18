# Minesweeper Game

This is a Minesweeper game written in C++ (C++17) using the SFML framework and built with CMake.

## Prerequisites
To build and run the project, you will need:
- A C++17 compiler (e.g. MSVC from Visual Studio 2022/2026)
- CMake 3.24+
- SFML 2.5+ (`graphics`, `window`, `system`)

The unit tests use [Catch2](https://github.com/catchorg/Catch2), which is fetched
automatically by CMake (`FetchContent`) and therefore needs internet access on the
first configure. Pass `-DMINESWEEPER_BUILD_TESTS=OFF` to skip them.

## Building and Running (Windows)

### Using vcpkg (recommended)
1. Install [vcpkg](https://github.com/microsoft/vcpkg) and the SFML package:
   ```shell
   vcpkg install sfml
   ```
2. Clone the repository:
   ```shell
   git clone https://github.com/IllusionOfControl/minesweeper.git
   cd minesweeper
   ```
3. Configure and build:
   ```shell
   cmake -B build -DCMAKE_TOOLCHAIN_FILE=<path-to-vcpkg>/scripts/buildsystems/vcpkg.cmake
   cmake --build build
   ```
4. Run the game (assets are copied next to the executable automatically):
   ```shell
   ./build/Debug/minesweeper.exe
   ```

### Using a downloaded SFML
1. Download SFML from https://www.sfml-dev.org/download/sfml/2.5.1/ and extract it.
2. Configure pointing CMake at it, then build:
   ```shell
   cmake -B build -DSFML_DIR=<path-to-sfml>/lib/cmake/SFML
   cmake --build build
   ```

## Running the tests
```shell
ctest --test-dir build --output-on-failure
```
The tests cover the pure game logic in `Board` (mine placement, flood fill, marking,
chord, win/lose, reset) and the `StateManager` stack behaviour. They are also run on
every push/PR by the GitHub Actions workflow in [`.github/workflows/ci.yml`](.github/workflows/ci.yml).

## Architecture
The code is split into small, focused pieces:

- `src/Board.{hpp,cpp}` — pure, SFML-free game logic (the board model, mine placement,
  reveal/flood-fill, marks, chord, win/lose). This is what the unit tests target.
- `src/states/` — screens implementing the `State` interface (`init/handleInput/update/draw`):
  main menu, difficulty menu, custom difficulty, about and the game screen. `GameState`
  only handles input and rendering and delegates the rules to `Board`.
- `src/managers/` — `AssetManager` (textures/fonts) and `StateManager` (a stack of screens).
- `src/gui/` — reusable widgets (`Button`, `Input`, `Indicator`, `Background`, `Container`,
  `SmileButton`) plus `WidgetFactory` for the shared menu/exit/background widgets.
- `src/MineSweeper.{hpp,cpp}` — owns the window, asset loading and the main loop; the
  `Context` it holds is shared with every state.

## How to Play
The objective is to clear the board without detonating any mines.

- **Left-click** a cell to reveal it. The first click is always safe. If the cell holds a
  mine the game is over; otherwise a number shows how many of the 8 neighbours are mines.
- **Right-click** to cycle a cell through flag → question mark → unmarked.
- **Middle-click** a revealed number whose flag count matches it to "chord" — reveal all of
  its remaining unflagged neighbours at once.
- Press **R** or click the smiley to start a new game.

To win, reveal every cell that is not a mine. Good luck!

---

*The assets were taken from [minesweeper]*

[minesweeper]: https://github.com/logalex96/Minesweeper
