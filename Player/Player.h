#pragma once
#include <iostream>
#include <vector>
#include "Cards.h"
#include "Map.h"
#include "Orders.h"
using namespace std;

class Player {
	public:
		//Default Constructor
		Player();
		//Copy constructor
		Player(const Player& player);
		//Parameterized constructor
		Player(string* name, Hand* hand, vector<Territory*>* territory, vector<Order*>* order, int*);
		//Destructor
		~Player();
		//returns name of Player
		string getName() const;
		//toDefend method that returns a list of territories to defend
		vector<Territory*> toDefend() const;
		//toDefend method that returns a list of territories to Attack
		vector<Territory*> toAttack() const;
		//issueOrder method that creates an order object and adds it to list of orders
		void issueOrder();
		//assignment operator
		Player& operator=(const Player& other);
		//sets name of Player
		void setName(string* setName);
		//stream insertion operator 
		friend ostream& operator <<(ostream& os, const Player& other);

		int getOrderSize() const;
		int getTerritoryOwnedSize() const;
		Order* getOrder(int index) const;
		int getReinforcementPool() const;
		void setReinforcementPool(int);


	//all data members are pointer types
	private:
		//name of player
		string* name;
		//hand of cards of player
		Hand* hand;
		//territories owned by player
		vector<Territory*>* territory;
		//list of orders of player
		vector<Order*>* order;

		int* reinforcementPool;

};


