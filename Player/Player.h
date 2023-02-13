#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "Orders.h"
#include "map.h"
#include "Cards.h"
using namespace std;

class Player {
	public:
		//Default Constructor
		Player();
		//Copy constructor
		Player(const Player& player);
		//Parameterized constructor
		Player(string* name, Hand* cardHand, vector<territory*> territories, vector<Order*> order);
		//Destructor
		~Player();
		//Assignment operator
		Player& operator=(const Player& other);
		//get name of player
		string* getName() const;
		//toDefend method that returns a list of territories to defend
		void toDefend() const;
		//toAttack method that returns a list of territories to Attack
		void toAttack() const;
		//issueOrder method that creates an order object and adds it to list of orders
		void issueOrder();
		//stream insertion operator
		friend ostream& operator >>(ostream& outs, const Player& player);

	private:
		//name of player
		string* name;
		//hand of cards of player
		Hand* cardHand;
		//territories owned by player
		vector<territory*> territories;
		//list of orders of player
		vector<Order*> orderList;

};
