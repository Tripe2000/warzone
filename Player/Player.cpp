#include "Player.h"
#include <algorithm>
#include <string>

//Sets default player
Player::Player() {
	this->name = nullptr;
	this->hand = nullptr;
	this->territory = nullptr;
	this->order = nullptr;
	this->reinforcementPool = nullptr;
}

// Parameterized constructor to create a new Player with attributes 
Player::Player(string* name, Hand* hand, vector<Territory*>* territory, vector<Order*>* order, int* pool) {
	this->name = new string(*name);
	this->hand = new Hand(*hand);
	this->territory = new vector<Territory*>(*territory);
	this->order = new vector<Order*>(*order);
	this->reinforcementPool = new int(*pool);
}

//Copy constructor 
Player::Player(const Player& player) {
	name = new string();
	*name = *player.name;

	hand = new Hand();
	*hand = *player.hand;

	territory = new vector<Territory*>;
	*territory = *player.territory;

	order = new vector<Order*>;
	*order = *player.order;

	reinforcementPool = new int();
	*reinforcementPool = *player.reinforcementPool;
}

//Destructor
Player::~Player() {
	delete name;
	name = nullptr;
	delete hand;
	hand = nullptr;
	delete territory;
	territory = nullptr;
	delete order;
	order = nullptr;
	delete reinforcementPool;
	reinforcementPool = nullptr;
}

//returns name of player
string Player::getName() const{
	return *name;
}

//For now lists an arbitrary list of territories to attack 
vector<Territory*> Player::toAttack() const {
	vector<Territory*> toAttack;
	vector<Territory*> notOwned;
	vector<Territory*> toDefend;
	toDefend = Player::toDefend();

	for (int i = 0; i < territory->size(); i++) {
		if (getName().compare((*territory)[i]->getTerritoryOwner()) != 0) {
			notOwned.push_back((*territory)[i]);
		}
	}

	for (int i = 0; i < toDefend.size(); i++) {
		for (int j = 0; j < notOwned.size(); j++) {
			if (toDefend[i]->isAdjacentTerritory(notOwned[j])) {
				if(toAttack.size()==0){
					toAttack.push_back(notOwned[j]);
				}
				else {
					for (int z = 0; z < toAttack.size(); z++) {
						if (notOwned[j] == toAttack[z]) {
							break;
						}
						else {
							toAttack.push_back(notOwned[j]);
						}
					}
				}
						
			}
		}
	}

	return toAttack;

	cout << "List of territories to be attacked by " << getName() << ": " << endl;
	for (int i = 0; i < toAttack.size(); i++) {
		cout << i + 1 << ". " << toAttack[i]->getName() << endl;
	}

}

//For now lists an arbitrary list of territories to defend
vector<Territory*> Player::toDefend() const {
	vector<Territory*> toDefend;
	for (int i = 0; i < territory->size(); i++) {
		if (getName().compare((*territory)[i]->getTerritoryOwner()) == 0) {
			toDefend.push_back((* territory)[i]);
		}
	}

	return toDefend;

	cout << "List of territories to be defended by " << getName() << ": " << endl;
	for (int i = 0; i < toDefend.size(); i++) {
		cout << i + 1 << ". " << toDefend[i]->getName() << endl;
	}

	
}

//Creates an order and adds it to order list 
void Player::issueOrder() {
	vector<Territory*> toDefend = Player::toDefend();
	vector<Territory*> toAttack = Player::toAttack();
	//Reinforcement phase
	cout << getName() << " select the territories to send reinforcement to:" << endl;
	for (int i = 0; i < toDefend.size(); i++) {
		cout << i+1 << ". " <<toDefend[i]->getName() << ": " << toDefend[i]->getArmies() << " armies." << endl;
	}
	bool check = true;
	while (check) {
		string name;
		cout << "You currently have " << getReinforcementPool() << " reinforcement to send." << endl;
		cout << "Enter the name of the territory you wish to add reinforcement to: " << endl;
		cin >> name;
		
		transform(name.begin(), name.end(), name.begin(), ::toupper);
		
		int count = 0;
		for (int i = 0; i < toDefend.size(); i++) {
			string nameTer = toDefend[i]->getName();
			transform(nameTer.begin(), nameTer.end(), nameTer.begin(), ::toupper);
			toDefend[i]->setName(nameTer);
			if (name == toDefend[i]->getName()) {
				int nbArmy;
				cout << "Enter number of reinforcement to send to " << toDefend[i]->getName() << endl;
				cin >> nbArmy;
				if (nbArmy<0 || nbArmy>getReinforcementPool()) {
					cout << "Invalid number of reinforcement" << endl;
				}
				else {
					cout << "Added " << nbArmy << " armies to " << toDefend[i]->getName() << endl;
					toDefend[i]->addArmies(nbArmy);
					setReinforcementPool(getReinforcementPool() - nbArmy);
					if (getReinforcementPool() == 0) {
						check = false;
					}
				}
			}
		}
	}
	cout << endl;
	cout << "Reinforcement phase now over." << endl;
	cout << "------------------------------------------------" << endl;

	//Move or attack orders
	cout << "Now select which army to move or attack: " << endl;
	cout << "Territories to defend:" << endl;
	for (int i = 0; i < toDefend.size(); i++) {
		cout << i + 1 << ". " << toDefend[i]->getName() << ": " << toDefend[i]->getArmies() << " armies." << endl;
	}
	cout << "---------------------------------------------------------------------------" << endl;
	cout << "Territories to attack:" << endl;
	for (int i = 0; i < toAttack.size(); i++) {
		cout << i + 1 << ". " << toAttack[i]->getName() << ": " << toAttack[i]->getArmies() << " armies." << endl;
	}
	bool checkIssue = true;
	while (checkIssue) {
		string territory;
		int nbArmies;
		string destination;
		string decision;
		cout << "Enter the name of the territory you wish to move or 'exit' to exit orders issuing phase: " << endl;
		cin >> territory;
		transform(territory.begin(), territory.end(), territory.begin(), ::toupper);
		if (territory == "EXIT") {
			checkIssue = false;
		}
		else {
			cout << "Enter the name of the territory you wish to move your amies to: " << endl;
			cin >> destination;
			cout << "Enter the number of armies to move to this territory: " << endl;
			cin >> nbArmies;
			//Advance* order = new Advance(territory, destination, nbArmies);
			//order->push_back(order);
			cout << "Your order was issed" << endl;
			cout << "Would you like to issue more orders? (Y/N)" << endl;
			cin >> decision;
			if (decision == "N") {
				checkIssue = false;
			}
			else if (decision == "Y") {
				checkIssue = true;
			}
		}
	}
	cout << "Orders Issuing phase now over." << endl;
	cout << "-------------------------------------------------------------" << endl;
}

//assignment operator 
Player& Player::operator=(const Player& other) {
	if (this != &other) {
		delete name;
		delete hand;
		delete territory;
		delete order;

		name = new string(*other.name);
		hand = new Hand(*other.hand);
		territory = new vector<Territory*>(*other.territory);
		order = new vector<Order*>(*other.order);
	}
	return *this;
}

//sets name of player 
void Player::setName(string* setName) {
	name = setName;
}

//stream insertion operator 
ostream& operator <<(ostream& os, const Player& other) {
	os << "Name: " << (other.getName()) << endl;
	os << "    Territories: " << endl;
	for (auto territory : *(other.territory)) {
		os << *territory << endl;
	}
	os << "    Hand: " << *(other.hand) << endl;
	
	return os;
}

//
int Player::getOrderSize() const {
	return order->size();
}

//
int Player::getTerritoryOwnedSize() const {
	int nb = toDefend().size();
	return nb;
}

//
Order* Player::getOrder(int index) const {
	if (index < 0 || index >= order->size()) {
		return nullptr;
	}
	return (*order)[index];
}

//
void Player::setReinforcementPool(int pool) {
	*reinforcementPool = pool;
}

//
int Player::getReinforcementPool() const {
	return *reinforcementPool;
}
