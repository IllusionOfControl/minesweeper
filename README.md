# Minesweeper Game

This is a Minesweeper game written in C++ using the SFML framework and built with CMake.

## Prerequisites
To build and run the project, you will need to install the following:
- CMake
- SFML framework

## Building and Running the Project (Windows)
### Using Library Linking
1. Download the SFML framework from the official website: https://www.sfml-dev.org/download/sfml/2.5.1/
2. Extract the contents of the zip file to a directory of your choice.
3. Clone the repository:
```shell
git clone https://github.com/username/minesweeper.git
```
4. Open a command prompt and navigate to the project directory. Create a build directory:
```shell
mkdir build
cd build
```
5. Generate the build files:
```shell
cmake -DCMAKE_BUILD_TYPE=Release -DSFML_ROOT=<path-to-sfml> ..
```
6. Make sure to replace <path-to-sfml> with the path to the directory where you extracted the SFML framework.
7. Build the project:
```shell
cmake --build .
```
This will generate an executable file called minesweeper.exe in the build directory.

To run the game, double-click the minesweeper.exe file.
### Using Vcpkg
1. Install Vcpkg by following the instructions on the official website: https://github.com/microsoft/vcpkg
2. Install the SFML framework:
Copy code
```shell
vcpkg install sfml
```
3. Clone the repository:

```shell
git clone https://github.com/username/minesweeper.git
```
4. Open a command prompt and navigate to the project directory. Create a build directory:
``` shell
mkdir build
cd build
```
5. Generate the build files:
```shell
cmake -DCMAKE_TOOLCHAIN_FILE=<path-to-vcpkg>/scripts/buildsystems/vcpkg.cmake -DCMAKE_BUILD_TYPE=Release ..
```
6. Make sure to replace <path-to-vcpkg> with the path to the directory where you installed Vcpkg.
7. Build the project:
```shell
cmake --build .
```
This will generate an executable file called minesweeper.exe in the build directory.

To run the game, double-click the minesweeper.exe file.

## How to Play

The objective of the game is to clear the board without detonating any mines.

To clear a cell, left-click on it. If the cell contains a mine, the game is over. If the cell does not contain a mine, a number is displayed indicating how many adjacent cells contain mines.

To flag a cell, right-click on it. This is useful for marking cells that you think contain mines.

To win the game, all non-mine cells must be cleared. Good luck!

---

*The assets where taken from [minesweeper]*

[minesweeper]: https://github.com/logalex96/Minesweeper