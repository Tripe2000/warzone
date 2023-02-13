#include <iostream>
using namespace std;
#include "Player.h"

//Sets default player
Player::Player() 
{
	string* name = nullptr;
	Hand* cardHand = nullptr;
	vector<territory*> territories;
	vector<Order*> orderList;
}

//asigns created player with name, hand of cards, territories, and list of orders
Player::Player(string* name, Hand* cardHand, vector<territory*> territories, vector<Order*> orderList) 
{
	this->name = new string(*name);
	this->cardHand = new Hand(*cardHand);
	this->territories = territories;
	this->orderList = orderList;
}

//Copy constructor
Player::Player(const Player& player)
{
	name = new string();
	*name = *player.name;
	
	cardHand = new Hand();
	*cardHand = *player.cardHand;
	
	territories = player.territories;
	orderList = player.orderList;
}

//Destructor 
Player::~Player()
{
	delete name;
	name = nullptr;
	delete cardHand;
	cardHand = nullptr;
	territories.clear();
	orderList.clear();
}

string* Player::getName() const
{
	return name;
}

ostream& operator <<(ostream& os, const Player& player) 
{
	os << "Name: " << *(player.getName()) <<endl;
	return os;
}

//assignment operator
Player& Player::operator=(const Player& other)
{
	if (this != &other) {
		//deallocate
		delete name;
		delete cardHand;
		territories.clear();
		orderList.clear();

		//allocate
		name = new string(*other.name);
		cardHand = new Hand(*other.cardHand);
		territories = other.territories;
		orderList = other.orderList;
	}
	return *this;
}

//For now lists an arbitrary list of territories to attack
void Player::toAttack() const
{
	for (int i = 0; i < territories.size(); i++)
	{
		cout << territories[i] << endl;
	}
}

//For now lists an arbitrary list of territories to defend
void Player::toDefend() const
{
	for (int i = 0; i < territories.size(); i++)
	{
		cout << territories[i] << endl;
	}
}

//Creates order and adds it to order list 
void Player::issueOrder()
{
	Order *order = new Order();
	orderList.push_back(order);
}