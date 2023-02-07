#pragma once
#include <string>

class Engine {
    private:
    int *currentState;

    public:
    Engine();
    bool execCommand(std::string command);
    std::string getCurrentState() const;
};