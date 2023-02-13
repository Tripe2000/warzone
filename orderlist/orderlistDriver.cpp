#include "Orders.h"

using namespace std;

int main()
{
	//orderlist object
	OrderList orderListObj;
	//types of orders
	Deploy deploy;
	Advance advanceTo;
	Bomb bomb;
	Blockade blockadeObj;
	Airlift airliftObj;
	Negotiate negotiateObj;

	//set orderlist according to the order type
	orderListObj.set_order_list(&deploy);
	orderListObj.set_order_list(&advanceTo);
	orderListObj.set_order_list(&bomb);
	orderListObj.set_order_list(&blockadeObj);
	orderListObj.set_order_list(&airliftObj);
	orderListObj.set_order_list(&negotiateObj);

	cout << "Orderlist Driver...\n" << endl;

	//display orderlist
	cout << "\n the orderlist has: " << endl;
	for (int i = 0; i < orderListObj.get_order_list()->size(); i++) {
		cout << "  " << orderListObj.get_order_list()->at(i)->get_type() << endl;
	}
	//delete order
	orderListObj.delete_order(&deploy);

	//display orderlist
	cout << "\n the orderlist has: " << endl;
	for (int i = 0; i < orderListObj.get_order_list()->size(); i++) {
		cout << "  " << orderListObj.get_order_list()->at(i)->get_type() << endl;
	}
	//move a order
	orderListObj.move(0, 4);
	//invalid order
	orderListObj.move(0, 8);
	
	//display orderlist
	cout << "\n the orderlist has: " << endl;
	for (int i = 0; i < orderListObj.get_order_list()->size(); i++) {
		cout << "  " << orderListObj.get_order_list()->at(i)->get_type() << endl;
	}
}
