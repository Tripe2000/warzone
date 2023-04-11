#include "gameEngine.h"
#include "commandProcessing.h"
#include <iostream>

int main(int argc, char* argv[]) {
    GameEngine * gameEngine = new GameEngine();

    if(argc < 2) {
        std::cout << "Incorrect Arguments" << std::endl;
    }
    
    else if(strcmp(argv[1], "-file") == 0) {
        //std::string file_name = "commands.txt";
        std::string file_name = argv[2];
        std::cout << file_name << std::endl;

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

    }
    
    else if(strcmp(argv[1], "-console") == 0) {
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