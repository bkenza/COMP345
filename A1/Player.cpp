#include "Player.h"
#include <vector>
#include <iostream>

using namespace std;

// Each player will have a collection of territories as well as a collection of cards, as well as an order list at the start of the game
Player::Player() {}

Player::Player(vector<Territory*> tList, vector<Cards*> cList, OrdersList oList)
{
    territoryList = &tList;
    cardList = &cList;
    orderList = oList;
}

//Destructor to call finalize() and free unwanted resources
Player::~Player()
{
    int tListSize = territoryList->size();
    for (int i = 0; i < tListSize; i++) // Delete memory for orders, which are always dynamically allocated.
        delete (*territoryList)[i];

    delete territoryList; // Delete the memory for the vector itself.

    int cListSize = cardList->size();
    for (int i = 0; i < cListSize; i++) // Delete memory for orders, which are always dynamically allocated.
        delete (*cardList)[i];

    delete cardList; // Delete the memory for the vector itself.

    /*int oListSize = orderList;
    for (int i = 0; i < oListSize; i++) // Delete memory for orders, which are always dynamically allocated.
        delete (*orderList)[i];

    delete orderList; // Delete the memory for the vector itself.*/
}

// Assign a list of territories to Player
void Player::setTerritoryList(vector<Territory*> tList)
{
    territoryList = &tList;
}

// Get player's territories
vector<Territory*> Player::getTerritoryList()
{
    return *territoryList;
}


// Assign a list of cards to a specified Player
void Player::setCardList(vector<Cards*> cList)
{
    cardList = &cList;
}

// Get a Player's list of cards
vector<Cards*> Player::getCardList()
{
    return *cardList;
}

// Assign a list of orders to a specified Player
void Player::setOrderList(OrdersList oList)
{
    orderList = oList;
}

// Get a Player's list of orders
OrdersList Player::getOrderList()
{
    return orderList;
}


// List of territories that are going to be defended
vector<Territory*> Player::toDefend()
{
    // Declare and initialize defendList
    vector<Territory*> defendList;

    // Loop through OrderList, if order is blockade, then create a list and add the territories
    /*for (auto o : territoryList)
    {
        if (o == )
        {
            // add to defendList
        }
    }*/
     return defendList;
}

// List of territories that are going to be attacked
vector<Territory*> Player::toAttack()
{
    //declare and initialize attackList
    vector<Territory*> attackList;

    // Loop through OrderList, if order is bomb or advance, then create a list and add the territories
    /*int listSize = orderList.listSize();
    for(int i = 0; i < listSize; i++)
    {

        if( (*orderList.getListOfOrders())[i]->getLabel() == "deploy" || (*orderList.getListOfOrders())[i]->getLabel() == "advance")
        {
            attackList.push_back(territoryList);
        }
    }*/
    //attackList.push_back(territoryList);
    return attackList;
}

// Method to allow a Player to make an Order and add it to the orderList
// Orders allowed are: deploy, advance, bomb, blockade, airlift, negotiate
void Player::issueOrder(string orderName)
{

    OrderFactory oFact; //Create OrderFactory to call createOrder method
    oFact.createOrder(orderName); //Create Order object

    //Add to Player's orderList
    if(oFact.createOrder(orderName) == nullptr)
    {
        cout << orderName << " cannot be added to the orders list!" << endl;
    }
    orderList.addOrder(oFact.createOrder(orderName));
}

