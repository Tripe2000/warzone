#pragma once
#include <string>

class GameEngine {
    private:
    int *currentState;
    bool executeCommand(int cmd);

    public:
    GameEngine();
    bool transitionState(std::string command);
    std::string getCurrentState() const;
};