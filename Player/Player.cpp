#include "Player.h"

//Sets default player
Player::Player() {
	this->name = nullptr;
	this->hand = nullptr;
	this->territory = nullptr;
	this->order = nullptr;
}

// Parameterized constructor to create a new Player with attributes 
Player::Player(string* name, Hand* hand, vector<Territory*>* territory, vector<Order*>* order) {
	this->name = new string(*name);
	this->hand = new Hand(*hand);
	this->territory = new vector<Territory*>(*territory);
	this->order = new vector<Order*>(*order);
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
}

//returns name of player
string Player::getName() const{
	return *name;
}

//For now lists an arbitrary list of territories to attack 
void Player::toAttack() const {
	for (int i = 0; i < territory->size(); i++) {
		cout << *(* territory)[i] << endl;
	}
}

//For now lists an arbitrary list of territories to defend
void Player::toDefend() const {
	for (int i = 0; i < territory->size(); i++) {
		cout << *(*territory)[i] << endl;
	}
}

//Creates an order and adds it to order list 
void Player::issueOrder() {
	Order* newOrder = new Order();
	order->push_back(newOrder);
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
