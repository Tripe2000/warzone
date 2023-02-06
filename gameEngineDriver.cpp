#include "GameEngine.h"
#include <iostream>

int main() {
    std::string input = NULL;
    while (true) {
        std::cout << "Enter next command: ";
        std::cin >> input;
        GameEngine::validate(input);
    }
    
    return 0;
}