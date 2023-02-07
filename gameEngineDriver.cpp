#include "gameEngine.h"
#include <iostream>

int main() {
    std::string input = "";
    bool possible = true;
    while (true) {
        std::cout << "Current state: " << getCurrentState() << std::endl;
        std::cout << "Enter next command: ";
        std::cin >> input;
        possible = execCommand(input);
        if(input == "exit") break;
        std::cout << "Valid: ";
        if(possible) std::cout << "True";
        else std::cout << "False";
        std::cout << std::endl << std::endl << std::endl;
    }
    
    return 0;
}