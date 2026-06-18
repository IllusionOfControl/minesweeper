include(FetchContent)

FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG v3.5.2
)
FetchContent_MakeAvailable(Catch2)

add_executable(minesweeper_tests
        BoardTest.cpp
        StateManagerTest.cpp
        ${CMAKE_SOURCE_DIR}/src/Board.cpp
        ${CMAKE_SOURCE_DIR}/src/managers/StateManager.cpp)
target_include_directories(minesweeper_tests PRIVATE ${CMAKE_SOURCE_DIR}/src)
target_link_libraries(minesweeper_tests PRIVATE Catch2::Catch2WithMain)

list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)
include(Catch)
catch_discover_tests(minesweeper_tests)
