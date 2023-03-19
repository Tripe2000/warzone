#include "gameEngine.h"
#include "commandProcessing.h"
#include <iostream>

int main() {
    GameEngine * gameEngine = new GameEngine();

    if(true) {
        std::string file_name = "commands.txt";

        int number_of_lines = 0;
        std::string line;
        std::ifstream myfile(file_name);
        while (std::getline(myfile, line)) {
            ++number_of_lines;
        }

        FileLineReader * lr = new FileLineReader(file_name);
        FileCommandProcessorAdapter * adapter = new FileCommandProcessorAdapter(gameEngine, lr);

        for(int i = 0; i < number_of_lines; i++) {
            std::string cmd = adapter->getCommand();
            std::cout << *adapter << std::endl;
            if(adapter->validate(cmd)) {
                gameEngine->transitionState(cmd);
            }
        }

        gameEngine->~GameEngine();
        adapter->~FileCommandProcessorAdapter();

    } else {
        CommandProcessor * commandProcessor = new CommandProcessor(gameEngine);

        while (true) {
            std::string cmd = commandProcessor->getCommand();
            std::cout << *commandProcessor << std::endl;
            if(commandProcessor->validate(cmd)) {
                gameEngine->transitionState(cmd);
            }
        }

        gameEngine->~GameEngine();
        commandProcessor->~CommandProcessor();
    }
    
    return 0;
}