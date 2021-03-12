project(minesweeper)
cmake_minimum_required(VERSION 3.17)
set(CMAKE_CXX_STANDARD 14)
add_executable(minesweeper main.cpp game.cpp)
find_package(SFML 2.5.1 COMPONENTS graphics audio REQUIRED)
target_link_libraries(minesweeper sfml-graphics sfml-audio)
file(COPY
        ${CMAKE_CURRENT_SOURCE_DIR}\\Fonts\\
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR}\\Fonts\\ )