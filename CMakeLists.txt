project(minesweeper)
cmake_minimum_required(VERSION 3.8)
set(CMAKE_CXX_STANDARD 17)
set(SOURCE_FILES ${SOURCE_FILES} MineSweeper.cpp MineSweeper.h)
set(SOURCE_FILES ${SOURCE_FILES} managers/InputManager.cpp managers/InputManager.h)
set(SOURCE_FILES ${SOURCE_FILES} managers/AssetManager.cpp managers/AssetManager.h)
set(SOURCE_FILES ${SOURCE_FILES} managers/StateManager.cpp managers/StateManager.h)
set(SOURCE_FILES ${SOURCE_FILES} states/State.h)
set(SOURCE_FILES ${SOURCE_FILES} states/MainMenuState.cpp states/MainMenuState.h)
set(SOURCE_FILES ${SOURCE_FILES} states/GameState.cpp states/GameState.h)
set(SOURCE_FILES ${SOURCE_FILES} )
set(SOURCE_FILES ${SOURCE_FILES} )
set(SOURCE_FILES ${SOURCE_FILES} )
set(SOURCE_FILES ${SOURCE_FILES} )
add_executable(minesweeper main.cpp header.h DEFINITIONS.h ${SOURCE_FILES})
find_package(SFML 2.5.1 COMPONENTS graphics audio REQUIRED)
target_link_libraries(minesweeper sfml-graphics sfml-audio)
file(COPY
        ${CMAKE_CURRENT_SOURCE_DIR}\\Fonts\\
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR}\\Fonts\\ )
file(COPY
        ${CMAKE_CURRENT_SOURCE_DIR}\\_Resources\\
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR}\\_Resources\\ )
file(COPY
        ${CMAKE_CURRENT_SOURCE_DIR}\\docs\\
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR}\\docs\\ )
file(COPY
        ${CMAKE_CURRENT_SOURCE_DIR}\\images\\
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR}\\images\\ )
file(COPY
        ${CMAKE_CURRENT_SOURCE_DIR}\\sounds\\
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR}\\sounds\\ )