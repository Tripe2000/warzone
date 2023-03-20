#include "Orders.h"

using namespace std;

int main()
{
	OrderList orders;

	Deploy *deploy=new Deploy;
	Advance *advance = new Advance;
	Bomb *bomb = new Bomb;
	Blockade *blockade = new Blockade;
	Airlift *airlift = new Airlift;
	Negotiate *negotiate = new Negotiate;

	orders.set_order_list(deploy);
	orders.set_order_list(advance);
	orders.set_order_list(bomb);
	orders.set_order_list(blockade);
	orders.set_order_list(airlift);
	orders.set_order_list(negotiate);


	//print orderlist
	cout << "\n the orderlist contains: " << endl;
	for (int i = 0; i < orders.get_order_list()->size(); i++) {
		cout <<"  "<< orders.get_order_list()->at(i)->get_type() << endl;
	}

	//delete an order
	orders.delete_order(deploy);

	//print orderlist
	cout << "\n the orderlist contains: " << endl;
	for (int i = 0; i < orders.get_order_list()->size(); i++) {
		cout << "  " << orders.get_order_list()->at(i)->get_type() << endl;
	}

	//move an order
	orders.move(0,4);
	//orders.move(0, 5);
	orders.move(0, 8);//invalid
	//print orderlist
	cout << "\n the orderlist contains: " << endl;
	for (int i = 0; i < orders.get_order_list()->size(); i++) {
		cout << "  " << orders.get_order_list()->at(i)->get_type() << endl;
	}

}
