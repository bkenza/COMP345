#include "Player.h"
#include <vector>
#include <iostream>

using namespace std;

// Each player will have a collection of territories as well as a collection of cards, as well as an order list at the start of the game
Player::Player() {}

Player::Player(vector<Territory*> tList, Deck pDeck, Hand pHand, OrdersList oList)
{
    territoryList = tList;
    playerDeck = pDeck.DeckCards;
    playerHand = pHand.HandCards;
    orderList = oList;
}

Player::Player(const Player &obj)
{
    territoryList = obj.territoryList;
    playerDeck = obj.playerDeck;
    playerHand = obj.playerHand;
    orderList = obj.orderList;
}

//Destructor to call finalize() and free unwanted resources
Player::~Player()
{
    int tListSize = territoryList.size();
    for (int i = 0; i < tListSize; i++) // Delete memory for orders, which are always dynamically allocated.
        delete territoryList[i];
   territoryList.clear(); // Delete the memory for the vector itself.*/

    int dListSize = playerDeck.size();
    for (int i = 0; i < dListSize; i++) // Delete memory for orders, which are always dynamically allocated.
        delete playerDeck[i];
    playerDeck.clear(); // Delete the memory for the vector itself.

    int hListSize = playerHand.size();
    for (int i = 0; i < dListSize; i++) // Delete memory for orders, which are always dynamically allocated.
        delete playerHand[i];
    playerHand.clear(); // Delete the memory for the vector itself.

    int oListSize = orderList.listSize();
    for (int i = 0; i < oListSize; i++) // Delete memory for orders, which are always dynamically allocated.
        delete (*orderList.getListOfOrders())[i];
    delete orderList.getListOfOrders(); // Delete the memory for the vector itself.*/
}

// Assign a list of territories to Player
void Player::setTerritoryList(vector<Territory*> tList)
{

    territoryList = tList;
}

// Get player's territories
vector<Territory*> Player::getTerritoryList()
{
    return territoryList;
}

// Assign a list of cards to a specified Player
void Player::setDeck(Deck d)
{
    playerDeck = d.DeckCards;
}

// Get a Player's list of cards
vector<Cards*> Player::getDeck()
{
    return playerDeck;
}

void Player::setHand(Hand h)
{
    playerHand = h.HandCards;
}

vector<Cards*> Player::getHand()
{
    return playerHand;
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


// Player's list of territories that are going to be defended
vector<Territory*> Player::toDefend()
{
    int tListSize = territoryList.size();
    for(int i = 1; i < tListSize; i++)
    {
        if(i % 3  == 0)
        {
            defendList.push_back(territoryList[i]);
        }
    }

    return defendList;
}

//Print function for Player's list of territories to be defended
void Player::printDefendList()
{
    for (auto t : defendList)
    {
        std::cout << "Player ID: " << t->getTerritoryPlayerID() << " | ";
        std::cout << "Territory ID: " << t->getTerritoryID() << " | ";
        std::cout << "Territory Name: " << t->getTerritoryName() << " | ";
        std::cout << "Continent Name: " << t->getContinent() << " | ";
        std::cout << "Number of Armies: " << t->getNumOfArmies() << "\n";
    }
}

// Player's list of territories that are going to be attacked
vector<Territory*> Player::toAttack()
{
    int tListSize = territoryList.size();
    for(int i = 0; i < tListSize; i++)
    {
        if(i % 2 == 0)
        {
            attackList.push_back(territoryList[i]);
        }
    }
    return attackList;
}

// Print function for Player's list of territories to be attacked
void Player::printAttackList()
{
    for (auto t : attackList)
    {
        std::cout << "Player ID: " << t->getTerritoryPlayerID() << " | ";
        std::cout << "Territory ID: " << t->getTerritoryID() << " | ";
        std::cout << "Territory Name: " << t->getTerritoryName() << " | ";
        std::cout << "Continent Name: " << t->getContinent() << " | ";
        std::cout << "Number of Armies: " << t->getNumOfArmies() << "\n";
    }
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

// Print function for Player's list of controlled territories
void Player::printTerritoryList()
{
    for (auto t : territoryList)
    {
        std::cout << "Player ID: " << t->getTerritoryPlayerID() << " | ";
        std::cout << "Territory ID: " << t->getTerritoryID() << " | ";
        std::cout << "Territory Name: " << t->getTerritoryName() << " | ";
        std::cout << "Continent Name: " << t->getContinent() << " | ";
        std::cout << "Number of Armies: " << t->getNumOfArmies() << "\n";
    }
}

// Print function for a Player's deck
void Player::printDeck()
{
    for (auto d : playerDeck)
    {
        cout << d->getCardType() << endl;
    }
}

// Print function for a Player's deck
void Player::printHand()
{
    for (auto h : playerHand)
    {
        cout << h->getCardType() << endl;
    }
}
