#include "gameEngine.h"
#include <iostream>
#include <string>

static const int ROWS = 10;
static const int COLUMNS = 12;
static int transitionTable[ROWS][COLUMNS] = {
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

// Utility function to turn the input to lower case
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

  if(command == "load_map") return 0;
  else if(command == "validate_map") return 1;
  else if(command == "add_player") return 2;
  else if(command == "assign_countries") return 3;
  else if(command == "issue_order") return 4;
  else if(command == "end_issue_orders") return 5;
  else if(command == "exec_order") return 6;
  else if(command == "end_exec_orders") return 7;
  else if(command == "win") return 8;
  else if(command == "play") return 9;
  else if(command == "end") return 10;
  else return 11;
}

// Default constructor
Engine::Engine() {
  currentState = new int(1);
}

// Return the current state
std::string Engine::getCurrentState() const {
  if(*currentState == 1) return "Start";
  else if(*currentState == 2) return "Map Loaded";
  else if(*currentState == 3) return "Map Validated";
  else if(*currentState == 4) return "Players Added";
  else if(*currentState == 5) return "Assign Reinforcements";
  else if(*currentState == 6) return "Issue Orders";
  else if(*currentState == 7) return "Execute Orders";
  else if(*currentState == 8) return "Win";
  else if(*currentState == 9) return "End";
  else return "Error";
}

// Execute the given command if valid from the current state
bool Engine::execCommand(std::string command) {
  bool possible;

  // Check if for the given command, the transition does not lead to the error state
  if(transitionTable[*currentState][commandIndex(command)] != 0) possible = true;
  else possible = false;

  // Change the current state if the command leads to a valid transition
  if(possible) {
    // MISSING: Add the actual execution of the given command here
    *currentState = transitionTable[*currentState][commandIndex(command)];
  }

  return possible;
}