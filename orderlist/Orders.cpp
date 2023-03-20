#pragma once
#include "Orders.h"
#include <iostream>
#include <algorithm>
#include <sstream>
#include <vector>


//Order&Order ::operator = (const Order&O)
//{
//	
//}
Order::Order() : player()
{

}


Order::Order(Player* player)
{
	this->player = player;
}
Order::Order(const Order& order)
{
	player = order.player;
	valid = order.valid;
}

Order::~Order()
{
	delete this ->player;
	delete this;
	
}
Order& Order::operator=(const Order& order)
{
	player = order.player;
	valid = order.valid;
	return *this;
}
bool Order::operator==(const Order& other)
{
	return player == other.player && valid == other.valid;
}



void Order::validate()
{
	cout << "validate if the order is valid" << endl;
	valid = true;
}

void Order::execute()
{
	if (valid) {
		cout << "executes the action..." << endl;
	}
}

void Order::set_type_id(int num)
{
	type_id = num;
}

string Order::get_type()
{
	return vec_type1.at(type_id);
}


std::ostream& operator << (std::ostream& o, const Order& order)
{
	return o << "An order is in the list";
}


void OrderList::set_order_list(Order* an_order)
{
	vec_order_list.push_back(an_order); //add an order
}

vector<Order*>* OrderList::get_order_list()
{
	return &vec_order_list;
}

void OrderList::delete_order(Order* oneOrder)
{
	for (int i = 0; i < vec_order_list.size(); i++) {
		if (oneOrder->get_type() == vec_order_list.at(i)->get_type()) {
			cout << "  deleting the order: " << oneOrder->get_type() << endl;
			vec_order_list.erase(vec_order_list.begin() + i);
			
			return;
		}
	}
}

void OrderList::move(int position, int new_position)
{
	if (position >= 0 && position < vec_order_list.size() && new_position >= 0 && new_position < vec_order_list.size())
	{
		vec_order_list.insert(vec_order_list.begin() + new_position, vec_order_list.at(position));
		vec_order_list.erase(vec_order_list.begin() + position);
	}
	else if (new_position == vec_order_list.size()  )
	{
		vec_order_list.push_back(vec_order_list.at(position));
		vec_order_list.erase(vec_order_list.begin() + position);
	}
	else {
		cout << "\n not valid position" << endl;
	}
}

Deploy::Deploy():Order()
{
	cout << "deploy is creating..." << endl;
	set_type_id(0);
}
Deploy::Deploy(Player* player, Territory* territory, unsigned int numOfArmies) : Order(player)
{
	this->territory = territory;
	this->numOfArmies = numOfArmies;
}

Deploy::Deploy(const Deploy& deploy) : Order(deploy)
{
	this->territory = deploy.territory;
	this->numOfArmies = deploy.numOfArmies;

}

Deploy::~Deploy()
{
	delete this->territory;
	delete this;
}

Deploy& Deploy:: operator=(const Deploy& deploy)
{
	Order::operator=(deploy);
	territory = deploy.territory;
	numOfArmies = deploy.numOfArmies;
	return *this;
}

bool Deploy::validate()  
{
	if (territory->getOwner() == getPlayer() && this->numOfArmies > 0)
		return true;
	return false;
}



string* Deploy::get_type()
{
	return &type1;
}

bool Deploy::execute()
{
	if (validate())
	{
		cout << "Deploying " << numOfArmies << " Armies." << endl;
		valid = true;

		territory->addTroops(numOfArmies);
		return true;
	}
	return false;
}

ostream& operator << (std::ostream& o, const Deploy& deploy)
{
	return o << "A deploy order has been issued";
}



Advance::Advance():Order()
{
	cout << "advance is creating..." << endl;
	set_type_id(1);
}

Advance::~Advance()
{
	delete this->current;
	delete this->next;
	delete this;
}
Advance::Advance(Player* player, Territory * current, Territory * next, unsigned int numOfArmies): Order(player)
{
	this->current = current;
	this->next = next;
	this->numOfArmies = numOfArmies;
}


Advance::Advance(const Advance& advance) :Order(advance)
{
	this->current = advance.current;
	this->next = advance.next;

}

Advance& Advance ::operator = (const Adavance& advance)
{
	Order:: operator =(advance);
	current = advance.current;
	next = advance.next;
	numOfArmies = advance.numOfArmies;
	return *this;
}

bool Advance::validate()
{
	if (current->getOwner() == getPlayer() && current->isAdjacent(next->index))
		return true;
	return false;
}

bool Advance::execute()
{
	if (validate())
	{
		executed = true;
		if (next->getOwner() == getPlayer())
		{
			int armiesToMove = std::min((int)numOfArmies, current->numOfArmies);
			if (armiesToMove != numOfArmies)
				numOfArmies = armiesToMove;
			current->removeTroops(numOfArmies);
			next->addTroops(numOfArmies);

			cout << "Advancing " << numOfArmies << "Armies from " << cuurent->name << " to " << next->name << endl;
		}
		else
		{
			while (next->numOfArmies > 0 || current->numOfArmies > 0)
			{
				srand(time(NULL));
				if (rand() % 10 < 6)
					next->removeTroops(1);
				else if (rand() % 10 < 7)
					current->removeTroops(1);
					numOfArmies--;
			}
			if (next->numOfArmies == 0)
			{
				next->setOwner(player);
				next->addTroops(numOfArmies);
			}
		}
		return true;
	}
	return false;
}


string Advance::get_type()
{
	return "advance";
}


ostream& operator << (std::ostream& o, const Advance& advance)
{
	return o << "An advance order has been issued";
}


Bomb::Bomb():Order()
{
	Territory(0, "source", 0);
	Territory(0, "target", 0);

}
Bomb::Bomb(Player* player, Territory* source, Territory* target) : Order(player)
{
	this->source = source;
	this->target = target;
}

Bomb::Bomb(const Bomb& bomb) :Order(bomb)
{
	this->source = bomb.source;
	this->target = bomb.target;
}


Bomb::~Bomb()
{
	this->source = NULL;
	this->target = NULL;

}
Bomb& Bomb::operator = (const Bomb & bomb)
{
	Order::operator = (bomb);
source = bomb.source;
target = bomb.target;
return *this;
}

bool Bomb::validate()
{
	if (source->isAdjacent(target->index) && course->getPlayer() && target->getOwner() != getPlayer())
		return true;
	return false;
}

bool Bomb::execute()
{
	if (validate())
	{
		executed = true;
		int numDestroyed = (int)(target->numOfArmies / 2.0);
		target->removeTroops(numDestroyed);
		cout << "Bombing" << target->name << "territory, reducing 1/2 of its forces." << endl;
		return true;
	}
	return false;
}

string Bomb::get_type()
{
	return "bomb";
}

ostream& operator << (std::ostream& o, const Bomb& bomb)
{
	return o << "A bomb order has been issed";
}





Blockade::Blockade(): Order()
{
	cout << "blockade is creating..." << endl;
	set_type_id(3);

}


Blockade::Blockade(Player* player, Territory* target): Order (player)
{
	this->target = target;
}

Blockade::Blockade(const Blockade& blockade) : Order(blockade)
{
	this->target = blockade.target;
}

Blockade::~Blockade()
{
	delete this->target;
	delete this;
}

Blockade& Blockade::operator = (const Blockade & blockade)
{
	Order:: operator = (blockade);
target = blockade.target;
return *this;
}

bool Blockade::validate()
{
	if (target->getOwner() == getPlyaer())
		return true;
	return false;
}

bool Blockade::execute()
{
	if (validate())
	{
		executed = true;
		target->addTroops(target->numOfArmies * 2);
		target->setOwner(new Player("Neutral"));
		cout << "Blockading " << target->name << " territory, double its forces, making it neutral." << endl;
		return true;

	}
	return false;
}

string Blockade::get_Type()
{
	return "blockade";
}

ostream& operator << (std::ostream& o, const Blockade& b)
{
	return o << " A blockade order has been issued";
}

Airlift::Airlift():Order()
{
	cout << "airlift is creating..." << endl;
	set_type_id(4);
}

Airlift::Airlift(Player* player, Territory* current, Territory* next, unsigned int numOfArmies): Order(player)
{
	this->current = current;
	this->next = next;
	this->numOfArmies = numOfArmies;

}

Airlift::Airlift(const Airlift& airlift) : Order(airlift)
{
	this->current = airlift.current;
	this->next = airlift.next;
}

Airlift::~Airlift()
{
	this->current = NULL;
	this->next = NULL;

}

Airlift& Airlift::operator = (const Airlift& airlift)
{
	Order::operator = (airlift);
	current = airlift.current;
	next = airlift.next;
	return *this;

}

bool Airlift::validate()
{
	if (current->getOwner() == getPlayer())
		return true;
	return false;
}

bool Airlift::execute()
{
	if (validate())
	{
		executed = true;
		if (next->getOwner() == getPlayer())
		{
			int armiesToMove = std::min((int)numOfArmies, current->numerOfArmies);
			if (armiesToMove != numOfArmies)
				numOfArmies = armiesToMove;
			current->removeTroops(numOfArmies);
			next->addTroops(numOfArmies);
		}

		else
		{
			while (next->numberOfArmies > 0 || current->numberOfArmies > 0)
			{
				srand(time(NULL));
				if (rand() % 10 < 6)
					next->removeTroops(1);
				else if (rand() % 10 < 7)
					current->removeTroops(1);
				numOfArmies--;
			}

			if (next->numberOfArmies == 0)
			{
				next->setOwner(player);
				next->addTroops(numOfArmies);

			}
		}
		cout << "Airlift " << numOfArmies << " arimes from " << current->name << " to " << next->name << "territory." << endl;
		return true;
	}
	return false;
}

string Airlift::get_type()
{
	return "airlift";
}

ostream& operator << (std::ostream& o, const Airlift& airlift) 
{
	return o << "An airlift order has been issued. " << endl;
}

Negotiate::Negotiate():Order()
{
	cout << "negotiate is creating..." << endl;
	set_type_id(5);
}

Negotiate::Negotiate(Player* current, Player* enemy) : Order(current)
{
	this->enemy = enemy;

}

Negotiate::Negotiate(const Negotiate& negotiate) : Order(negotiate)
{
	this->enemy = negotiate.enemy;
}

Negotiate:: ~Negotiate()
{
	this->enemy = NULL;
}


Negotiate& Negotiate :: operator = (const Negotiate& negotiate)
{
	Order:: operator = (negotaite);
	this->enemy = negotiate.enemy;
	return *this;
}

bool Negotiate::validate()
{
	if (getPlayer() != enemy)
		return true;
	return false;
}

bool Negotiate::execute()
{
	if (validate())
	{
		executed = true;
		cout << "Negotiate" << endl;
		return true;
	}
	return false;
}

string Negotiate::get_type()
{
	return "negotiate";
}

ostream& operator << (std::ostream& o, const Negotiate& Negotiate)
{
	return o<<"A negotiate order has been issed."
}

vector<Order* >OrderList::get_order_list()
{
	vector<Order*> o;
	for (int i = 0; i < orderlist.size(); i++)
	{
		o.push_back(orderList.at(i));

	}
	return o;
}

OrderList::OrderList(const OrderList& ol)
{
	orderList = ol.orderList;
}

