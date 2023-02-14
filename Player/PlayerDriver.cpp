#include "Player.h"

int main()
{
	//create pointer to name
	string name = "nick";
	string* ptrName = &name;

	//create pointer to Hand 
	Hand* hand = new Hand();

	//create pointer to a vector of pointers to Territories
	vector<Territory*>* territory = new vector<Territory*>;
	Territory* ter1 = new Territory(1, "territory 1", 1);
	Territory* ter2 = new Territory(2, "territory 2", 2);
	territory->push_back(ter1);
	territory->push_back(ter2);

	//create pointer to a vector of pointers to Orders
	vector<Order*>* order = new vector<Order*>;
	Order* order1 = new Order();
	order1->set_type_id(1);
	Order* order2 = new Order();
	order2->set_type_id(2);
	order->push_back(order1);
	order->push_back(order2);

	//create player1 using parameterized constructor
	Player* player1 = new Player(ptrName, hand, territory, order);
	//test issueOrder
	(*player1).issueOrder();
	//test toAttack
	cout << "toAttack method" << endl;
	(*player1).toAttack();
	//test toDefend
	cout << "\ntoDefend method" << endl;
	(*player1).toDefend();
	//test getName method
	cout << "\ngetName for created player:" << endl;
	cout << (*player1).getName() << "\n" <<endl;

	Player player2 = *player1;
	string* newName = new string("argelie");
	//test set name method
	player1->setName(newName);
	cout << "Get name for first player with changed name" << endl;
	cout << (*player1).getName() << endl;
	cout << "Get name for second player to see if assignment operator works for deep copy" << endl;
	cout << player2.getName() << "\n" << endl;

	cout << "Testing the stream insertion operator" << endl;
	cout << player2;

	//Creating a player using default constructor
	Player* player3 = new Player();

	//Creating a player using a copy constructor 
	Player* player4 = new Player(player2);
	string* name2 = new string("ame");
	player4->setName(name2);
	cout << "Names of player 2 and 4 after using copy constructor" << endl;
	cout << "Player 2: " << player2.getName() << endl;
	cout << "Player 4: " << player4->getName() << endl;


	delete player1;
	delete player3;
	delete player4;
}
