#include "gameEngine.h"
#include <iostream>

int main() {
    Engine engine = Engine();
    std::string input = "";
    bool possible = true;

    while (true) {
        std::cout << "Current state: " << engine.getCurrentState() << std::endl;
        std::cout << "Enter command: ";

        // Get input, exit if input is "exit"
        std::cin >> input;
        if(input == "exit") break;

        // Attempt state change, get result
        possible = engine.execCommand(input);

        if(possible) std::cout << "Accepted";
        else std::cout << "Rejected command";

        std::cout << std::endl << std::endl << std::endl;
    }
    
    return 0;
}