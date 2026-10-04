# Minesweeper v2

[![CI](https://github.com/IllusionOfControl/minesweeper/actions/workflows/ci.yml/badge.svg)](https://github.com/IllusionOfControl/minesweeper/actions/workflows/ci.yml)
[![C++17](https://img.shields.io/badge/C%2B%2B-17-blue.svg)](https://en.wikipedia.org/wiki/C%2B%2B17)
[![CMake](https://img.shields.io/badge/CMake-3.24%2B-informational.svg)](https://cmake.org)
[![SFML](https://img.shields.io/badge/SFML-3.x-green.svg)](https://www.sfml-dev.org)
[![Catch2](https://img.shields.io/badge/Catch2-v3-orange.svg)](https://github.com/catchorg/Catch2)

This is **Minesweeper v2**, a modern implementation of the classic Minesweeper game written in **C++17** using the **SFML** framework and built with **CMake**.

This version represents a comprehensive overhaul of the original project. The codebase has been redesigned and refactored to meet production requirements and industry software engineering standards:
- **Clean separation of concerns:** Core game rules and board logic are encapsulated in a pure, SFML-independent domain model (`Board`), enabling deterministic behavior and headless unit testing.
- **Robustness and safety:** Undefined behavior, uninitialized state, and switch fall-through issues have been resolved. The recursive flood fill has been replaced with a safe iterative stack-based algorithm to prevent call-stack overflows.
- **Modern C++ design:** Adoption of C++17 idioms, `constexpr` constants in place of preprocessor macros, strong typing (`enum class`), and secure random generation via `std::mt19937`.
- **State machine and modular UI:** Screen transitions are managed through a stack-based state manager, supported by a reusable component-driven GUI system.
- **Persistence and observability:** Game results are persisted to JSON using `nlohmann_json` with cross-platform filesystem path resolution, alongside structured logging powered by `spdlog` and `fmt`.
- **Automated verification:** Built-in unit tests powered by Catch2 and continuous integration through GitHub Actions.

Detailed notes and history from the refactoring process are preserved in the [`legacy/`](legacy/) directory.

---

## Features

- **Difficulty Presets and Custom Mode:**
  - *Beginner:* 9×9 board, 10 mines
  - *Intermediate:* 16×16 board, 40 mines
  - *Expert:* 30×16 board, 99 mines
  - *Custom:* User-defined board dimensions and mine count with input validation
- **Guaranteed Safe First Click:** The first revealed tile is never a mine.
- **Chording Support:** Middle-clicking a revealed numbered cell whose adjacent flag count matches its value uncovers all surrounding unflagged cells.
- **Leaderboard and Persistence:** Records your best completion times and saves player statistics to JSON across sessions.
- **Smooth Window Management:** A single operating system window dynamically resizes between menus and varying board sizes without flickering.
- **Structured Logging:** Configurable log levels with colored console outputs for easy diagnostics and debugging.

---

## Prerequisites

To build and run the game, ensure you have:
- A **C++17** compliant compiler (MSVC from Visual Studio 2022/2026, GCC 9+, or Clang 10+)
- **CMake 3.24+**
- [vcpkg](https://github.com/microsoft/vcpkg) for dependency management

The project uses manifest mode (`vcpkg.json`) to automatically fetch and configure:
- **SFML** (`graphics`, `window`, `system`, `audio`, `network`)
- **spdlog** and **fmt**
- **nlohmann-json**

Unit tests use **Catch2 v3**, fetched automatically by CMake via `FetchContent`.

---

## Building and Running (Windows)

### 1. Clone the Repository
```shell
git clone https://github.com/IllusionOfControl/minesweeper.git
cd minesweeper
```

### 2. Configure with CMake
Point CMake to your vcpkg toolchain file (or use your `$env:VCPKG_ROOT` environment variable):
```shell
cmake -B build -A x64 -DCMAKE_TOOLCHAIN_FILE="<path-to-vcpkg>/scripts/buildsystems/vcpkg.cmake"
```

### 3. Build
```shell
cmake --build build --config Release
```
*Note: Game assets (`_Resources`) are copied to the executable directory automatically as part of the post-build step.*

### 4. Run the Game
```shell
./build/Release/minesweeper.exe
```

---

## Building and Running (Linux)

### 1. Install System Dependencies
vcpkg builds SFML 3 from source on Linux and links against system windowing, graphics, audio, and device libraries.

**Fedora:**
```shell
sudo dnf install -y \
    gcc-c++ cmake ninja-build git \
    systemd-devel libX11-devel libXrandr-devel libXcursor-devel libXi-devel \
    mesa-libGL-devel alsa-lib-devel freetype-devel libvorbis-devel flac-devel
```

**Ubuntu / Debian:**
```shell
sudo apt-get update && sudo apt-get install -y \
    build-essential cmake ninja-build git curl zip unzip tar pkg-config \
    libudev-dev libx11-dev libxrandr-dev libxcursor-dev libxi-dev \
    libgl1-mesa-dev libasound2-dev libfreetype-dev libvorbis-dev libflac-dev
```

### 2. Set Up vcpkg
If you have vcpkg installed via Fedora package manager (`dnf`), clone the ports repository into the expected root directory:
```shell
source /etc/profile.d/vcpkg.sh
git clone https://github.com/microsoft/vcpkg.git "$VCPKG_ROOT"
cd "$VCPKG_ROOT" && ./bootstrap-vcpkg.sh -disableMetrics
```

Otherwise, clone and bootstrap vcpkg manually:
```shell
git clone https://github.com/microsoft/vcpkg.git ~/vcpkg
~/vcpkg/bootstrap-vcpkg.sh -disableMetrics
export VCPKG_ROOT="$HOME/vcpkg"
```

### 3. Configure and Build
```shell
cmake -B build -G Ninja \
  -DCMAKE_TOOLCHAIN_FILE="$VCPKG_ROOT/scripts/buildsystems/vcpkg.cmake" \
  -DCMAKE_BUILD_TYPE=Release

cmake --build build
```
*Note: Game assets (`_Resources`) are copied to the executable directory automatically as part of the post-build step.*

### 4. Run the Game
```shell
./build/minesweeper
```

---

## Running the Unit Tests

The test suite covers the domain game logic (mine placement, safe opening, flood fill, flagging, chording, win/loss evaluation, reset) and the state manager stack lifecycle.

Run tests using `ctest`:
```shell
# Windows (multi-config):
ctest --test-dir build -C Release --output-on-failure

# Linux:
ctest --test-dir build --output-on-failure
```

To configure the build without unit tests, pass `-DMINESWEEPER_BUILD_TESTS=OFF` during CMake configuration.

---

## How to Play

| Action | Control |
|---|---|
| **Reveal Cell** | **Left-click** (the first click is always safe) |
| **Flag / Mark Cell** | **Right-click** (cycles through Flag 🚩 → Question Mark ❓ → Unmarked) |
| **Chord (Open Neighbours)** | **Middle-click** on an opened number matching the count of flagged neighbours |
| **Restart Game** | Press **R** or click the smiley face in the top bar |
| **Navigate UI** | Use the on-screen buttons to switch screens, change difficulty, or view high scores |

To win the game, reveal all cells that do not contain mines.

---

## Credits

- Game sprites and graphical assets are sourced from [logalex96/Minesweeper](https://github.com/logalex96/Minesweeper).
