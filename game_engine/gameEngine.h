#pragma once
#include <string>
#include <list>
#include <iostream>

class GameEngine {
    private:
    int *currentState;
    bool executeCommand(std::string command);
    void startTournament(std::list<std::string> mapList, std::list<std::string> playerStrategiesList, int numberOfGames, int maxTurns);
    //By Nicolas
    vector<Player*> playerList;

    public:
    GameEngine();
    ~GameEngine();
    GameEngine(const GameEngine &obj);
    GameEngine& operator =(const GameEngine &obj);
    bool transitionState(std::string);
    std::string getCurrentState() const;
    int getState() const;
    friend std::ostream& operator <<(std::ostream &output, const GameEngine &obj);
    
    //By Nicolas 
    void mainGameLoop();
    void reinforcementPhase();
    void issueOrdersPhase();
    void executeOrdersPhase();
    
    //by dev
    void startupPhase();
    void addPlayer();
    void gameStart();
};

std::string toLower(std::string);
int* commandIndex(std::string);
bool isPlayer(std::string);

// Available commands/transitions
const int LOAD_MAP = 0;
const int VALIDATE_MAP = 1;
const int ADD_PLAYER = 2;
const int ASSIGN_COUNTRIES = 3;
const int ISSUE_ORDER = 4;
const int END_ISSUE_ORDERS = 5;
const int EXEC_ORDER = 6;
const int END_EXEC_ORDERS = 7;
const int WIN = 8;
const int PLAY = 9;
const int END = 10;
const int ERROR = 11;
const int TOURNAMENT = 12;

// Available states
const int ERROR_STATE = 0;
const int START_STATE = 1;
const int MAP_LOADED_STATE = 2;
const int MAP_VALIDATED_STATE = 3;
const int PLAYERS_ADDED_STATE = 4;
const int ASSIGN_REINFORCEMENTS_STATE = 5;
const int ISSUE_ORDERS_STATE = 6;
const int EXECUTE_ORDERS_STATE = 7;
const int WIN_STATE = 8;
const int END_STATE = 9;
const int TOURNAMENT_STATE = 10;

const int ROWS = 11;
const int COLUMNS = 13;