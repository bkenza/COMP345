#include "Orders.h"

int omain()
{
    OrderFactory factory;
    OrdersList list;

    list.addOrder(factory.createOrder("deploy"));
    list.addOrder(factory.createOrder("advance"));
    list.addOrder(factory.createOrder("bomb"));
    list.addOrder(factory.createOrder("blockade"));
    list.addOrder(factory.createOrder("airlift"));
    list.addOrder(factory.createOrder("negotiate"));

    cout << "\n***********************************************************\n" << endl;

    list.deleteOrder(1);
    list.deleteOrder(5);
    list.deleteOrder(3);

    cout << "\n***********************************************************\n" << endl;

    list.moveOrder(1, 3);
    list.moveOrder(2, 1);
    list.moveOrder(3, 2);

    cout << "\n***********************************************************\n" << endl;

    cout << "NEWWWWWWWWWWWW LIIIIIISTTTTTTTTTTTTT" << endl;

    OrdersList test;

    test.addOrder(factory.createOrder("deploy"));
    test.addOrder(factory.createOrder("bomb"));
    test = list;

    cout << test;

    cout << test.getListOfOrders();

    return 0;
}