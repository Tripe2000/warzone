#include "gameEngine.h"
#include "commandProcessing.h"
#include <iostream>

int main() {
    GameEngine * gameEngine = new GameEngine();

    if(true) {
        std::string file_name = "commands.txt";

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

    } else {
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
    
    //ASSIGNMENT 2 PART 4
    ////create pointer to name
	string name = "nick";
	string* ptrName = &name;

	////create pointer to Hand 
	Hand* hand = new Hand();

	////create pointer to a vector of pointers to Territories
	vector<Territory*>* territory = new vector<Territory*>;
	Territory* ter1 = new Territory(1, "Canada", 1);
	Territory* ter2 = new Territory(2, "Mexico", 1);
	ter1->addBorders(ter2);
	ter2->addBorders(ter1);
	ter1->setTerritoryOwner("nick");
	ter2->setTerritoryOwner("nick");
	territory->push_back(ter1);
	territory->push_back(ter2);

	//create second player
	string name2 = "argelie";
	string* ptrName2 = &name2;
	Hand* hand2 = new Hand();
	vector<Order*>* orderPlayer2 = new vector<Order*>;
	int reinforcement2 = 0;
	int* reinforcementPtr2 = &reinforcement2;

	//create territories owned by opposing player
	vector<Territory*>* territory2 = new vector<Territory*>;
	Territory* ter3 = new Territory(3, "United States", 1);
	Territory* ter4 = new Territory(4, "Vietnam", 2);
	Territory* ter5 = new Territory(5, "Philippines", 2);
	Territory* ter6 = new Territory(6, "Cambodia", 2);
	Territory* ter7 = new Territory(7, "Japan", 2);
	Territory* ter8 = new Territory(8, "South Korea", 2);
	Territory* ter9 = new Territory(9, "Brazil", 3);
	Territory* ter10 = new Territory(10, "Argentina", 3);
	Territory* ter11= new Territory(11, "Ecuador", 3);
	Territory* ter12= new Territory(12, "Panama", 3);
	Territory* ter13= new Territory(13, "Columbia", 3);
	Territory* ter14= new Territory(14, "Peru", 3);
	territory2->push_back(ter1);
	territory2->push_back(ter2);
	territory2->push_back(ter3);
	territory2->push_back(ter4);
	territory2->push_back(ter5);
	territory2->push_back(ter6);
	territory2->push_back(ter7);
	territory2->push_back(ter8);
	territory2->push_back(ter9);
	territory2->push_back(ter10);
	territory2->push_back(ter11);
	territory2->push_back(ter12);
	territory2->push_back(ter13);
	territory2->push_back(ter14);
	ter1->addBorders(ter3);
	ter2->addBorders(ter3);
	ter3->addBorders(ter1);
	ter3->addBorders(ter2);
	ter3->setTerritoryOwner("argelie");
	ter4->setTerritoryOwner("argelie");
	ter5->setTerritoryOwner("argelie");
	ter6->setTerritoryOwner("argelie");
	ter7->setTerritoryOwner("argelie");
	ter8->setTerritoryOwner("argelie");
	ter9->setTerritoryOwner("argelie");
	ter10->setTerritoryOwner("argelie");
	ter11->setTerritoryOwner("argelie");
	ter12->setTerritoryOwner("argelie");
	ter13->setTerritoryOwner("argelie");
	ter14->setTerritoryOwner("argelie");
	territory->push_back(ter3);
	territory->push_back(ter4);
	territory->push_back(ter5);
	territory->push_back(ter6);
	territory->push_back(ter7);
	territory->push_back(ter8);
	territory->push_back(ter9);
	territory->push_back(ter10);
	territory->push_back(ter11);
	territory->push_back(ter12);
	territory->push_back(ter13);
	territory->push_back(ter14);

	////create pointer to a vector of pointers to Orders
	vector<Order*>* orderPlayer1 = new vector<Order*>;
	Order* order1 = new Order();
	order1->set_type_id(1);
	Order* order2 = new Order();
	order2->set_type_id(2);
	orderPlayer1->push_back(order1);
	orderPlayer1->push_back(order2);

	//create pointer to an int for reinforcement pool
	int reinforcement = 0;
	int* reinforcementPtr = &reinforcement;

	////create player1 using parameterized constructor
	Player* player1 = new Player(ptrName, hand, territory, orderPlayer1, reinforcementPtr);
	Player* player2 = new Player(ptrName2, hand2, territory2, orderPlayer2, reinforcementPtr2);
	vector<Player*>* playerList = new vector<Player*>;
	playerList->push_back(player1);
	playerList->push_back(player2);
	GameEngine* gameEngine = new GameEngine();
	gameEngine->setPlayerList(playerList);
	gameEngine->mainGameLoop();
    
    delete player1;
    delete player2;
    
    return 0;
}
