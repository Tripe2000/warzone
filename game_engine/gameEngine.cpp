#include "gameEngine.h"
#include <iostream>
#include <string>

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
int* commandIndex(std::string command) {
  command = toLower(command);

  if(command == "loadmap") return new int(LOAD_MAP);
  else if(command == "validatemap") return new int(VALIDATE_MAP);
  else if(command == "addplayer") return new int(ADD_PLAYER);
  else if(command == "assigncountries") return new int(ASSIGN_COUNTRIES);
  else if(command == "issueorder") return new int(ISSUE_ORDER);
  else if(command == "endissueorders") return new int(END_ISSUE_ORDERS);
  else if(command == "execorder") return new int(EXEC_ORDER);
  else if(command == "endexecorders") return new int(END_EXEC_ORDERS);
  else if(command == "win") return new int(WIN);
  else if(command == "play") return new int(PLAY);
  else if(command == "end") return new int(END);
  else return new int(ERROR);
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

int GameEngine::getState() const {
  return *(this->currentState);
}

// Execute the given command if valid from the current state
bool GameEngine::transitionState(std::string command) {
  // Get transition we are attempting to make from the table
  int *cmd = commandIndex(command);
  int attemptedTransition = transitionTable[*currentState][*cmd];

  // Check if the transition does not lead to the error state
  bool possible;
  if(attemptedTransition != ERROR_STATE) possible = true;
  else possible = false;

  // If the transition does not lead to an error state, run the command
  if(possible) {
    // Change the current state if the command executes correctly
    if(executeCommand(cmd)) *currentState = attemptedTransition;
  }

  // Deallocate cmd and remove dangling pointer
  delete cmd; cmd = NULL;
  return possible;
}

// Run the given command
bool GameEngine::executeCommand(int *cmd) {
  std::cout << "Running command: ";

  // MISSING: Add the actual execution of the given command instead of just printing it
  switch(*cmd) {
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

//By Nicolas
//Reinforcement phase
void GameEngine::reinforcementPhase() {
    for (int i = 0; i < playerList.size(); i++) {
        int numArmies = max((playerList[i]->getTerritoryOwnedSize()/3), 3);
        playerList[i]->setReinforcementPool(numArmies);
    }
    
}

//Issue order phase
void GameEngine::issueOrdersPhase() {
    for (int i = 0; i < playerList.size(); i++) {
        playerList[i]->issueOrder();
    }
}

//Execute orders phase
void GameEngine::executeOrdersPhase() {

    //
    int maxOrders = 0;
    for (const auto& player : playerList) {
        maxOrders = max(maxOrders, player->getOrderSize());
    }

    //
    for (int i = 0; i < maxOrders; i++) {
        for (auto& player: playerList) {
            if (i<player->getOrderSize()) {
                Order* order = player->getOrder(i);
                order->execute();
            }
        }
    }
}


//Execute main game loop
void GameEngine::mainGameLoop() {
    bool check = true;

    while (check)
    {
        cout << "Reinforcement Phase:" << endl;
        reinforcementPhase();
        issueOrdersPhase();
        executeOrdersPhase();

        for (int i = 0;i < playerList.size();i++)
        {
            if (playerList[i]->toDefend().size() == 195 || playerList.size() == 1)
            {
                cout << "Winner is " << playerList[i]->getName() << endl;
                check = false;
            }
            if (playerList[i]->toDefend().size() == 0)
            {
                cout << playerList[i]->getName() << " is eliminated from the game." << endl;
                playerList.erase(playerList.begin() + i);
            }
        }
    }
}

void GameEngine::setPlayerList(vector<Player*>* playerList) {
    this->playerList = *playerList;
}
// by dev
Map map;
void GameEngine::startupPhase() {
    std::string command;
    bool mapLoaded = false;
    bool mapValidated = false;
    bool playersAdded = false;

    while (true) {
        std::cout << "Enter a command to start the game:" << std::endl;
        std::cin >> command;
        if (command == "loadmap") {
            std::string filename;
            std::cin >> filename;
            map = readfile(filename);
            mapLoaded = true;
        } else if (command == "validatemap") {
            if (validate(map))
	        {
		        cout << "the map is valid!!" << endl;
	        }
        	else
        	{
        		cout << "the map is not valid!!" << endl;
        	}
        } else if (command == "addplayer") {
            if (!mapValidated) {
                std::cout << "Error: map not validated." << std::endl;
            } else {
                string playerName;
                cin >> playerName;
                addPlayer();
                playersAdded = true;
            }
        } else if (command == "gamestart") {
            if (!playersAdded) {
                std::cout << "Error: players not added." << std::endl;
            } else {
                distributeTerritories();
                determineOrderOfPlay();
                giveInitialArmies();
                drawInitialCards();
                switchToPlayPhase();
                break;
            }
        } else {
            std::cout << "Invalid command." << std::endl;
        }
    }
}
void GameEngine::addPlayer() {
    do{
        cout << "Enter the number of players you want to have (2-6): ";
        cin >> numOfPlayers; // add input validation
        vector<Territory*> territory;
        vector<Card*> card;
        vector<Order*> order;
        if(numOfPlayers > MAX_NUM_PLAYER || numOfPlayers < MIN_NUM_PLAYER){
            cout << "Invalid input, please enter again!" << endl;
        }
    }while(numOfPlayers>MAX_NUM_PLAYER || numOfPlayers < MIN_NUM_PLAYER);

    for(int i = 0; i < numOfPlayers; i++){
        cout << "Please enter the player name for player ID: " << i + 1 << " Player: " << endl;
        cin >> playerName;
        playerlist.push_back(new Player(i, playerName));
    }
}
void GameEngine::gameStart(){
    //assign territory to players in round-robin fashion
    cout << "\n The territories are assigned in the following order: " << endl;

    for (int i = 0; i < map.territories.size(); i++) {
        map.territories[i]->setPlayerID((playerlist.at(i % numOfPlayers))->getPID());
        playerlist.at(i % numOfPlayers)->territories.push_back(map.territories[i]);
        string territoryPlayer = playerlist.at(i % numOfPlayers)->getName();
        string territoryName = map.territories[i]->getTName();

        cout << setw(12) << "Territory: " << territoryName << ", owned by " <<  territoryPlayer << endl;
    }
    //initialize 50 armies to each player
    for (int k = 0; k < numOfPlayers; k++) {
        (playerlist.at(k))->setReinforcementPool(50);
    }

    //determine the order of play randomly
    shufflePlayerList();

    //initialize a card deck
    cout << "<Initialize Deck>" << endl;
    cout << "Deck size now is: " << endl;
    cout << deck->getCards().size() << endl;
    cout << "Draw 2 cards from deck:" << endl;
    for(int i = 0; i < numOfPlayers; i++){
        playerlist[i]->handCard.push_back(deck->draw());
        playerlist[i]->handCard.push_back(deck->draw());
    }

    for(int i = 0; i < numOfPlayers; i++){
        cout << *(playerlist[i]) << endl;
    }
}
