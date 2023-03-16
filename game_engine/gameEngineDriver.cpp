#include "gameEngine.h"
#include <iostream>

int main() {
    GameEngine gameEngine = GameEngine();
    std::string input = "";
    bool possible = true;

    while (true) {
        // Print current state and request next command
        std::cout << gameEngine;

        // Attempt state change
        possible = gameEngine.transitionState(input);

        // Print if command was rejected
        if(!possible) std::cout << "Rejected command";

        // Add some extra lines
        std::cout << std::endl << std::endl << std::endl;
    }

    gameEngine.~GameEngine();
    
    return 0;
}