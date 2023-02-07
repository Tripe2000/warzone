#include "gameEngine.h"
#include <iostream>
#include <string>

// Available commands/transitions
static const int LOAD_MAP = 0;
static const int VALIDATE_MAP = 1;
static const int ADD_PLAYER = 2;
static const int ASSIGN_COUNTRIES = 3;
static const int ISSUE_ORDER = 4;
static const int END_ISSUE_ORDERS = 5;
static const int EXEC_ORDER = 6;
static const int END_EXEC_ORDERS = 7;
static const int WIN = 8;
static const int PLAY = 9;
static const int END = 10;
static const int ERROR = 11;

// Available states
static const int ERROR_STATE = 0;
static const int START_STATE = 1;
static const int MAP_LOADED_STATE = 2;
static const int MAP_VALIDATED_STATE = 3;
static const int PLAYERS_ADDED_STATE = 4;
static const int ASSIGN_REINFORCEMENTS_STATE = 5;
static const int ISSUE_ORDERS_STATE = 6;
static const int EXECUTE_ORDERS_STATE = 7;
static const int WIN_STATE = 8;
static const int END_STATE = 9;

static int transitionTable[10][12] = {
  // load_map, validate_map, add_player, assign_countries, issue_order, end_issue_orders,
  //          exec_order, end_exec_orders, win, play, end, error
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },   // Error
  { 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },   // Start
  { 2, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },   // Map Loaded
  { 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0 },   // Map Validated
  { 0, 0, 4, 5, 0, 0, 0, 0, 0, 0, 0, 0 },   // Players Added
  { 0, 0, 0, 0, 6, 0, 0, 0, 0, 0, 0, 0 },   // Assign Reinforcements
  { 0, 0, 0, 0, 6, 7, 0, 0, 0, 0, 0, 0 },   // Issue Orders
  { 0, 0, 0, 0, 0, 0, 7, 5, 8, 0, 0, 0 },   // Execute Orders
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 9, 0 },   // Win
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }    // End
};

// Utility function to turn a string to lower case
std::string toLower(std::string upper) {
  char c = 'a';
  std::string lower = "";

  for(int i = 0; i < upper.length(); i++) {
    c = upper[i];
    lower.push_back(char(tolower(c)));
  }

  return lower;
}

// Get the transition table column index for a given command
int commandIndex(std::string command) {
  command = toLower(command);

  if(command == "load_map") return LOAD_MAP;
  else if(command == "validate_map") return VALIDATE_MAP;
  else if(command == "add_player") return ADD_PLAYER;
  else if(command == "assign_countries") return ASSIGN_COUNTRIES;
  else if(command == "issue_order") return ISSUE_ORDER;
  else if(command == "end_issue_orders") return END_ISSUE_ORDERS;
  else if(command == "exec_order") return EXEC_ORDER;
  else if(command == "end_exec_orders") return END_EXEC_ORDERS;
  else if(command == "win") return WIN;
  else if(command == "play") return PLAY;
  else if(command == "end") return END;
  else return ERROR;
}

// Return the current state as a string
std::string GameEngine::getCurrentState() const {
  if(*currentState == START_STATE) return "Start";
  else if(*currentState == MAP_LOADED_STATE) return "Map Loaded";
  else if(*currentState == MAP_VALIDATED_STATE) return "Map Validated";
  else if(*currentState == PLAYERS_ADDED_STATE) return "Players Added";
  else if(*currentState == ASSIGN_REINFORCEMENTS_STATE) return "Assign Reinforcements";
  else if(*currentState == ISSUE_ORDERS_STATE) return "Issue Orders";
  else if(*currentState == EXECUTE_ORDERS_STATE) return "Execute Orders";
  else if(*currentState == WIN_STATE) return "Win";
  else if(*currentState == END_STATE) return "End";
  else return "Error";
}

// Execute the given command if valid from the current state
bool GameEngine::transitionState(std::string command) {
  // Get transition we are attempting to make from the table
  int cmd = commandIndex(command);
  int attemptedTransition = transitionTable[*currentState][cmd];

  // Check if the transition does not lead to the error state
  bool possible;
  if(attemptedTransition != ERROR_STATE) possible = true;
  else possible = false;

  // If the transition does not lead to an error state, run the command
  if(possible) {
    // Change the current state if the command executes correctly
    if(executeCommand(cmd)) *currentState = attemptedTransition;
  }

  return possible;
}

// Run the given command
bool GameEngine::executeCommand(int cmd) {
  std::cout << "Running command: ";

  // MISSING: Add the actual execution of the given command instead of just printing it
  switch(cmd) {
    case LOAD_MAP:
      std::cout << "Load Map" << std::endl;
      return true;

    case VALIDATE_MAP:
      std::cout << "Validate Map" << std::endl;
      return true;

    case ADD_PLAYER:
      std::cout << "Add Player" << std::endl;
      return true;

    case ASSIGN_COUNTRIES:
      std::cout << "Assign Countries" << std::endl;
      return true;

    case ISSUE_ORDER:
      std::cout << "Issue Order" << std::endl;
      return true;

    case END_ISSUE_ORDERS:
      std::cout << "End Issue Orders" << std::endl;
      return true;

    case EXEC_ORDER:
      std::cout << "Exec Order" << std::endl;
      return true;

    case END_EXEC_ORDERS:
      std::cout << "End Exec Order" << std::endl;
      return true;

    case WIN:
      std::cout << "Win" << std::endl;
      return true;

    case PLAY:
      std::cout << "Play" << std::endl;
      return true;

    case END:
      std::cout << "End" << std::endl;
      return true;

    default:
      std::cout << "Invalid command, nothing happened" << std::endl;
      return false;
  }
}

// Default constructor
GameEngine::GameEngine() {
  currentState = new int(START_STATE);
}

// Copy constructor
GameEngine::GameEngine (const GameEngine &obj) {
  currentState = new int;
  *currentState = *obj.currentState;
}

// Assignment operator
GameEngine& GameEngine::operator =(const GameEngine &obj) { 
  currentState = obj.currentState;
  return *this;
}

// Stream insertion operator
std::ostream& operator <<(std::ostream &output, const GameEngine &obj) { 
  output << "Current state: " << obj.getCurrentState() << std::endl;
  return output;            
}

// Destructor
GameEngine::~GameEngine() {
  delete currentState;
  currentState = NULL;
}