#include <vector>
#include <iostream>
#include "Player.h"
#include "Map.h"
#include "Cards.h"
#include "Orders.h"

using namespace std;
/**
 * Each player will have a collection of territories as well as a
 * collection of cards, as well as an order list at the start of the game
 */
Player::Player()
{
    playerID;
}

Player::Player(GameEngine* ge)
{
    playerID;
    gameEngine = ge;
    orderList = new OrdersList;
    phase;
}

/**
 * Constructor
 * @param tList
 * @param hand
 * @param oList
 */
Player::Player(vector<Territory*> tList, Hand* hand, OrdersList* oList)
{
    territoryList = tList;
    playerHand = hand;
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

    delete orderList;
}
int Player::getPlayerID()
{
    return playerID;
}

void Player::setPlayerID(int playerId)
{
    playerID = playerId;
}

// Assign a list of territories to Player
/*void Player::setTerritoryList(vector<Territory *> tList)
{
    territoryList = tList;
}*/

void Player::setPhase(string ph)
{
    phase = ph;
}

string Player::getPhase()
{
    return phase;
}

// Get player's territories
vector<Territory *>* Player::getTerritoryList()
{
    return &territoryList;
}

/*void Player::setMap(Map *map)
{
    playerMap = map;
}*/

// Assign a list of cards to a specified Player
void Player::setHand(Hand *hand)
{
    playerHand = hand;
}

/*Map* Player::getMap()
{
    return playerMap;
}*/

// Get a Player's list of cards
Hand *Player::getHand()
{
    return playerHand;
}

// Assign a list of orders to a specified Player
void Player::setOrderList(OrdersList* oList)
{
}


// Get a Player's list of orders
OrdersList* Player::getOrderList()
{
    return orderList;
}

// List of territories that are going to be defended
vector<Territory *> Player::toDefend()
{
    return defendList;
}

//Print function for Player's list of territories to be defended
void Player::printDefendList()
{
    // Declare and initialize defendList
    //vector<Territory *> defendList = toDefend();
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
vector<Territory *> Player::toAttack()
{
    return attackList;
}

// Print function for Player's list of territories to be attacked
void Player::printAttackList()
{
    //vector<Territory *> attackList = toAttack();
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
// Player uses one of the cards in their hand to issue an order that corresponds to the card in question
void Player::issueOrder(string orderName)
{
    if (orderName != "deploy" && reinforcementPool > 0)
    {
        cout << "Invalid Order! You can select orders other than deploy only when you have"
             << " no armies in the reinforcement pool!" << endl;
    }

    while (reinforcementPool > 0)
    {
        cout << "\nDeployment phase!" << endl;

        int targetTerritoryID;
        int amount;

        cout << "\nInput a territory ID where you wish to deploy your armies!" << endl;
        cin >> targetTerritoryID;

        do
        {
            cout << "\nInput the number of armies you want to deploy!" << endl;
            cin.clear();
            cin.ignore();
            cin >> amount;
        } while (amount > reinforcementPool || amount < 1);

        reinforcementPool -= amount;

        Territory* targetTerritory = gameEngine->getMap()->getTerritoryById(targetTerritoryID);

        orderList->addOrder(new deploy(*targetTerritory, *this, amount));

        return;
    }

    if (orderName == "advance")
    {
        int sourceTerritoryID;
        int targetTerritoryID;
        int amount;

        cout << "\nInput a source territory by territory ID" << endl;
        cin >> sourceTerritoryID;
        cout << "\nInput a destination territory by territory ID" << endl;
        cin >> targetTerritoryID;

        Territory* sourceTerritory = gameEngine->getMap()->getTerritoryById(sourceTerritoryID);
        Territory* targetTerritory = gameEngine->getMap()->getTerritoryById(targetTerritoryID);

        do
        {
            cout << "\nInput the number of armies you want to advance!" << endl;
            cin >> amount;

        } while (amount > sourceTerritory->getNumOfArmies() || amount < 1);

        sourceTerritory->setNumOfArmies(sourceTerritory->getNumOfArmies() - amount);
        orderList->addOrder(new AdvanceOrder::advance(*sourceTerritory, *targetTerritory, *this, amount));
    }

    else if (orderName == "blockade")
    {
        int targetTerritoryID;

        cout << "\nPlease enter territory ID:" << endl;
        cin >> targetTerritoryID;

        Territory* targetTerritory = gameEngine->getMap()->getTerritoryById(targetTerritoryID);
        orderList->addOrder(new blockade(*targetTerritory,*this));
    }

    else if(orderName == "airlift")
    {
        int sourceTerritoryID;
        int targetTerritoryID;
        int amount;

        cout << "\nPlease enter source territory ID:" << endl;
        cin >> sourceTerritoryID;

        cout << "\nPlease enter destination territory ID:" << endl;
        cin >> targetTerritoryID;

        Territory* sourceTerritory = gameEngine->getMap()->getTerritoryById(sourceTerritoryID);
        Territory* targetTerritory = gameEngine->getMap()->getTerritoryById(targetTerritoryID);

        do
        {
            cout << "\nPlease enter amount:" << endl;
            cin >> amount;

        } while (amount > sourceTerritory->getNumOfArmies() || amount < 1);

        sourceTerritory->setNumOfArmies(sourceTerritory->getNumOfArmies() - amount);
        orderList->addOrder(new airlift(*sourceTerritory, *targetTerritory, *this, amount));
    }

    else if(orderName == "negotiate")
    {
        int targetPlayerID;

        cout << "Please enter a player's ID that you want to negotiate with: " << endl;
        cin >> targetPlayerID;

        Player* targetPlayer = gameEngine->getPlayerByID(targetPlayerID);

        orderList->addOrder(new negotiate(*targetPlayer, *this));
    }

    else if(orderName == "bomb")
    {
        int targetTerritoryID;

        cout << "Please enter target territory ID:" << endl;
        cin >> targetTerritoryID;

        Territory* targetTerritory = gameEngine->getMap()->getTerritoryById(targetTerritoryID);

        orderList->addOrder(new bomb(*targetTerritory, *this));
    }
}

// Method that creates an order and adds it to the player’s list of orders and then returns the card to the deck
void Player::play(Deck *currentDeck, Cards *card)
{
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

        cout << "Your" << usedCard.getCardType() << "card has been used and sent to deck" << endl;
};

/*
 * Print method for player's territory list
 */
void Player::printTerritoryList() {
    for (auto t : *getTerritoryList())
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
    for(int i = 0; i < gameEngine->getMap()->Continents.size(); i++)
    {
        int numOfTerritoriesInContinentMap = gameEngine->getMap()->Continents[i]->territories.size();
        int playerTerritoryIsInContinentCount;

        for(int j = 0; j < territoryList.size(); j++)
        {
            if(territoryList.at(j)->getContinent() == gameEngine->getMap()->Continents[i]->getContinentName())
            {
                playerTerritoryIsInContinentCount++;
            }
        }

        if(playerTerritoryIsInContinentCount == numOfTerritoriesInContinentMap)
        {
            return true;
        }
    }
    return false;
}

void Player::addFriendly(int targetPlayerID)
{
    friendlyPlayers.push_back(targetPlayerID);
}

bool Player::canAttack(int targetPlayerID)
{
    int listSize = friendlyPlayers.size();

    for(int i = 0; i < listSize; i++)
    {
        if (friendlyPlayers[i] == targetPlayerID)
        {
            return false;
        }
    }

    return true;
}

void Player::clearFriends()
{
    friendlyPlayers.clear();
}

GameEngine* Player::getGE()
{
    return gameEngine;
}