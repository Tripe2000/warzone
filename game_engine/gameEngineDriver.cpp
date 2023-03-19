#include "gameEngine.h"
#include "commandProcessing.h"
#include <iostream>

int main() {
    GameEngine * gameEngine = new GameEngine();
    CommandProcessor * commandProcessor = new CommandProcessor(gameEngine);

    while (true) {
        std::string cmd = commandProcessor->getCommand();
        std::cout << *commandProcessor << std::endl;
        /*if(commandProcessor->validate(cmd)) {
            gameEngine->transitionState(cmd);
        }*/
    }

    gameEngine->~GameEngine();
    commandProcessor->~CommandProcessor();
    
    return 0;
}