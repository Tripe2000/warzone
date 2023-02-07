#pragma once
#include <string>

class GameEngine {
    private:
    int *currentState;
    bool executeCommand(int cmd);

    public:
    GameEngine();
    ~GameEngine();
    GameEngine(const GameEngine &obj);
    GameEngine& operator =(const GameEngine &obj);
    bool transitionState(std::string command);
    std::string getCurrentState() const;
    friend std::ostream& operator <<(std::ostream &output, const GameEngine &obj);
};