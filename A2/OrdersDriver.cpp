#include "Orders.h"

using std::cout;
using std::endl;

int main()
{
    OrderFactory factory;
    OrdersList list;

    cout << "\n********** ADDING ORDERS **********\n" << endl;

    list.addOrder(factory.createOrder("deploy"));
    list.addOrder(factory.createOrder("advance"));
    list.addOrder(factory.createOrder("bomb"));
    list.addOrder(factory.createOrder("blockade"));
    list.addOrder(factory.createOrder("airlift"));
    list.addOrder(factory.createOrder("negotiate"));

    cout << "\n********** DELETING ORDERS **********\n" << endl;

    list.deleteOrder(1);
    list.deleteOrder(5);
    list.deleteOrder(3);

    cout << "\n********** MOVING ORDERS **********\n" << endl;

    list.moveOrder(1, 3);
    list.moveOrder(2, 1);
    list.moveOrder(3, 2);

    cout << "\n********** COPYING LIST USING COPY C'TOR **********\n" << endl;

    OrdersList ctorList = OrdersList(list);
    cout << ctorList;

    cout << "\n********** COPYING LIST USING = OPERATOR **********\n" << endl;

    OrdersList a;
    a.addOrder(factory.createOrder("deploy"));
    a.addOrder(factory.createOrder("bomb"));
    a = list;
    cout << a;

    cout << "\n********** EXECUTING ORDERS FROM LIST **********\n";

    /*list.executeOrders();*/

    cout << "\n********** PRINTING ALL THE LISTS **********\n";

    cout << "Printing the original list!:\n" << list << endl;
    cout << "Printing the c'tor list!:\n" << ctorList << endl;
    cout << "Printing = operator list!:\n" << a << endl;

    cout << "\n********** PRINTING ALL THE LISTS AGAIN + OPERATIONS **********\n";

    list.addOrder(factory.createOrder("deploy"));
    list.addOrder(factory.createOrder("airlift"));
    ctorList.deleteOrder(2);
    cout << "Printing the original list!:\n" << list << endl;
    cout << "Printing the c'tor list!:\n" << ctorList << endl;
    cout << "Printing = operator list!:\n" << a << endl;

    return 0;
}
