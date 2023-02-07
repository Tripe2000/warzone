#pragma once
#include <string>

class Engine {
    private:
    int *currentState;
    bool runCommand(int cmd);

    public:
    Engine();
    bool transitionState(std::string command);
    std::string getCurrentState() const;
};