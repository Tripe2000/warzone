#pragma once 
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

class Territory;
class Player;

class Order
{
public :
	Order();
	Order(Player* player);
	Order(const Order& other);
	virtual ~Order();
	Order& operator = (const Order& other);
	bool operator == (const Order& other);



	//check of the oder is valid 
	virtual bool validate();
	//execute method    
	virtual bool execute();
	
	//set type of the subclass
	void set_type_id(int num);
	string get_type();
	const Player* getPlayer();
	void setPlayer(Player* player);
	Player* player;


private :
	bool valid;
	vector<string> vec_type1 = { "deploy", "advance", "bomb", "blockade", "airlift", "negotiate" };
	int type_id;
protected:
	bool executed = false;
};

class Deploy : public Order 
{

public:
	Deploy();
	Deploy(Player* player, Territory* territory, unsigned int numOfArmies);
	Deploy(const Deploy& deploy);
	~Deploy();
	Deploy& operator = (const Deploy& deploy);
	virtual bool validate();
	virtual bool execute();
	friend ostream& operator << (std::ostream& o, const Deploy& deploy);

	string* get_type();
private:
	Territory* territory;
	unsigned int numOfArmaies;
	string type1 = { "deploy" };
};

class Advance : public Order {
public:
	Advance();
	Advance(Player* player, Territory* current, Territory* next, unsigned int numOfArmies);
	Advance(const Advance& advance);
	~Advance();
	Advance& operator = (const Advance& advance);
	virtual bool validate();
	virtual bool execute();
	friend ostream& operator << (std::ostream& o, const Advance& advance);

private:
	Territory* current;
	Territory* next;
	unsigned int numOfArmaies;
};

class Bomb : public Order 
{
public:
	Bomb();
	Bomb(Player* player, Territory* source, Territory* target);
	Bomb(const Bomb& bomb);
	~Bomb();
	Bomb& operator = (const Bomb& bomb);

	virtual bool validate();
	virtual bool execute();
	friend ostream& operator << (std::ostream& o, const Bomb& bomb);

private:
	Territory* source;
	Territory* target;
};

class Blockade : public Order
{
public:
	Blockade();
	Blockade(Player* player, Territory* target);
	Blockade(const Blockade& blockade);
	~Blockade();
	Blockade& operator = (const Blockade& blockade);
	virtual bool validate();
	virtual bool execute();
	friend ostream& operator << (std::ostream& o, const Blockade& blockade);
private:
	Territory* target;
};

class Airlift : public Order
{
public:
	Airlift();
	Airlift(Player* player, Territory* cuurent, Territory* next, unsigned int numOfArmies);
	Airlift(const Airlift& airlift);
	~Airlift();
	Airlift& operator = (const Airlift& airlift);
	
	virtual bool validate();
	virtual bool execute();
	friend ostream& operator << (std::ostream& o, const Airlift& airlift);
private:
	Territory* current;
	Territory* next;
	unsigned int numOfArmies;
};

class Negotiate : public Order
{
public:
	Negotiate();
	Negotiate(Player* current, Player* enemy);
	Negotiate(const Negotiate& negotiate);
	~Negotiate();
	virtual bool validate();
	virtual bool execute();
	friend ostream& operator << (std::ostream& o, const Negotiate& negatiate);

private:
	Player* enemy;
};

class OrderList
{
public:
	OrderList();
	OrderList(const OrderList& orderList);
	~OrderList();
	OrderList& operator = (const OrderList& orderList);
	void set_order_list(Order* an_order);
	vector<Order*>* get_order_list();
	//delete an order
	void delete_order(Order* oneOrder);
	//move
	void move(int position, int new_position);

	void remove(int index);

	void add(Order* order);

	friend ostream& operator <<(std::ostream& o, const OrderList& ol);


private:
	vector<Order*> vec_order_list; //store the orders
};


