#include "gameEngine.h"
#include <iostream>

int main() {
    Engine engine = Engine();
    std::string input = "";
    bool possible = true;

    while (true) {
        // Print current state and request next command
        std::cout << "Current state: " << engine.getCurrentState() << std::endl;
        std::cout << "Enter command: ";
        std::cin >> input;

        // Exit if input is "exit"
        if(input == "exit") break;

        // Attempt state change
        possible = engine.execCommand(input);

        // Print if command was accepted
        if(possible) std::cout << "Accepted";
        else std::cout << "Rejected command";

        // Add some extra lines
        std::cout << std::endl << std::endl << std::endl;
    }
    
    return 0;
}