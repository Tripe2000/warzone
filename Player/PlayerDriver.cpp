#include "Player.h"

int main()
{
	string name = "nick";
	string* ptrName = &name;

	vector<territory*> territories;
	territory *ter1 = new territory(1, "territory1", 1);
	territory *ter2 = new territory(2, "territory2", 2);
	territories.push_back(ter1);
	territories.push_back(ter2);

	Hand* cardHand = new Hand();

	vector<Order*> orderList;
	Order* order1 = new Order();
	Order* order2 = new Order();
	orderList.push_back(order1);
	orderList.push_back(order2);

	Player* player1 = new Player(ptrName, cardHand, territories, orderList);
	(*player1).toAttack();
	(*player1).toDefend();
	(*player1).issueOrder();

	Player* player2 = new Player(*player1);
	cout << player1 << endl;
	cout << player2 << endl;
}