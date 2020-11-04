#include "Player.h"
#include <vector>
#include <iostream>

using namespace std;
/**
 * Each player will have a collection of territories as well as a
 * collection of cards, as well as an order list at the start of the game
 */
Player::Player() {
    playerID =  int(0);
}

/**
 * Constructor
 * @param tList
 * @param hand
 * @param oList
 */
Player::Player(vector<Territory*> tList, Hand hand, OrdersList oList)
{
    territoryList = tList;
    playerHand = &hand;
    orderList = oList;
}

Player::Player(const Player &obj)
{
    territoryList = obj.territoryList;
    playerHand = obj.playerHand;
    orderList = obj.orderList;
}

//Destructor to call finalize() and free unwanted resources
Player::~Player()
{
    int tListSize = territoryList.size();
    for (int i = 0; i < tListSize; i++) // Delete memory for orders, which are always dynamically allocated.
        delete &territoryList[i];
   territoryList.clear(); // Delete the memory for the vector itself.*/

    int cListSize = playerHand->HandCards.size();
    for (int i = 0; i < cListSize; i++) // Delete memory for orders, which are always dynamically allocated.
        delete (playerHand->HandCards)[i];

    int hListSize = playerHand->HandCards.size();
    for (int i = 0; i < hListSize; i++) // Delete memory for orders, which are always dynamically allocated.
        delete playerHand->HandCards[i];
    playerHand->HandCards.clear(); // Delete the memory for the vector itself.
    delete playerHand;

    delete &playerHand->HandCards; // Delete the memory for the vector itself.
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
void Player::setHand(Hand *hand)
{
    playerHand = hand;
}

// Get a Player's list of cards
Hand* Player::getHand() {
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


// List of territories that are going to be defended
vector<Territory*> Player::toDefend()
{
    // Declare and initialize defendList
    vector<Territory*> defendList;

    // Loop through OrderList, if order is blockade, then create a list and add the territories
    int tListSize = territoryList.size();
    for(int i = 1; i < tListSize; i++)
    {
        if (i % 3  == 0)
        {
            defendList.push_back(territoryList[i]);
        }
    }
    return defendList;
}

//Print function for Player's list of territories to be defended
void Player::printDefendList()
{
    // Declare and initialize defendList
    vector<Territory*> defendList = toDefend();
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
    vector<Territory*> attackList;
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
    vector<Territory*> attackList = toAttack();
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
};

// Method that creates an order and adds it to the player’s list of orders and then returns the card to the deck
void Player::play(Deck *currentDeck, Cards *card) {
// create an order & add it to player's order list

    issueOrder(card->getCardType());

    int removalCounter = 0;
    Cards usedCard;

    // Remove card from current hand
    for (int p =0; p < playerHand->HandCards.size(); p++) {
        if (playerHand->HandCards[p]->getCardType() == card->getCardType() && removalCounter == 0) {
            usedCard = *playerHand->HandCards[p];
            playerHand->HandCards.erase(playerHand->HandCards.begin() + p);
            removalCounter++;
        }
    }

    // Return current card to the deck & shuffle it
    currentDeck->DeckCards.push_back(&usedCard);
    currentDeck->shuffleDeck();
};

/*
 * Print method for player's territory list
 */
void Player::printTerritoryList() {
    for (auto t : getTerritoryList())
    {
        std::cout << "Player ID: " << t->getTerritoryPlayerID() << " | ";
        std::cout << "Territory ID: " << t->getTerritoryID() << " | ";
        std::cout << "Territory Name: " << t->getTerritoryName() << " | ";
        std::cout << "Continent Name: " << t->getContinent() << " | ";
        std::cout << "Number of Armies: " << t->getNumOfArmies() << "\n";
    }
}

/*
 * Setting player's reinforcement pool
 */
void Player::setReinforcementPool(int n)
{
    reinforcementPool = n;
}

/*
 * Getting player's reinforcement pool
 */
int Player::getReinforcementPool()
{
    return reinforcementPool;
}

/* For every Continent vector in Map obj, it will store its size and while iterating through player's territory list,
 * checks whether a territory's continent owned by a player matches the Continent name Continents[i] of map obj,
 * if so we increment the playerTerritoryInContinentCount and then we check if it matches with Map Continent[i]'s size
 * if so then we can conclude that a player owns all territories in a particular continent and gains bonus power!
 */
bool Player::ownAllTerritoryInContinent()
{
    for(int v = 0; v < Map::Continents.size(); v++)
    {
        int numOfTerritoriesInContinentMap = Map::Continents[v]->territories.size();
        int playerTerritoryInContinentCount;

        for(int j = 0; j < territoryList.size(); j++)
        {
            if(territoryList.at(j)->getContinent() == Map::Continents[v]->getContinentName())
            {
                playerTerritoryInContinentCount++;
            }
        }

        if(playerTerritoryInContinentCount == numOfTerritoriesInContinentMap)
        {
            return true;
        }
    }
    return false;
}