#include <iostream>

#include "Game.h"

int main() {
    std::cout << "Hello SDL Test v0.1" << std::endl;
    Game game;
    game.start();
    std::cout << "Game Over!" << std::endl;
    return 0;
}
