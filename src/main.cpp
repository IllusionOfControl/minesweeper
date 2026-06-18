#include <iostream>
#include "MineSweeper.hpp"

int main() {
    try {
        MineSweeper();
    } catch (const std::exception &e) {
        std::cerr << "Fatal error: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}
