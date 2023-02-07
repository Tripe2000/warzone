#pragma once
#include <string>

class Engine {
    private:
    int *currentState;
    bool executeCommand(int cmd);

    public:
    Engine();
    bool transitionState(std::string command);
    std::string getCurrentState() const;
};