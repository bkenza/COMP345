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
    int id, amount, sourceID, destID, pID;

    if(orderName == "deploy")
    {

        cout << "Input a territory ID where you wish to deploy your armies!" << endl;
        cin >> id;


        cout << "Input the number of armies you want to deploy" << endl;
        cin >> amount;

        //vector<Territory*> gameMapTerritoryList = gameEngine->getMap()->Territories;

        for(int i = 0; i < territoryList.size(); i++)
        {
            //cout << territoryList[i]->getTerritoryID() << endl;
            if(territoryList[i]->getTerritoryID() == id)
            {
                cout << "Adding territory "<< territoryList[i]->getTerritoryName() <<
                " (" << territoryList[i]->getTerritoryID() << ") "<< "to defendList" << endl;
                defendList.push_back(territoryList[i]);
                cout << "\nYour defend list will now look like this" <<  endl;
                printDefendList();
                cout << "\nAdding order to order list" << endl;
                orderList->addOrder(new deploy());
            }
        }
    }

    else if(orderName == "advance")
    {
        int inputSourceID, inputDestID;
        cout << "Input a source by territory ID" << endl;
        cin >> inputSourceID;
        cout << "Input a destination by territory ID" << endl;
        cin >> inputDestID;

        //Territory* source = new Territory();
        Territory* dest;

        vector<Territory*> gameMapTerritoryList = gameEngine->getMap()->Territories;

        // To find input source territory in the map, in a seperate loop incase the source happens to be last element in the list
        for(int i = 0; i < gameMapTerritoryList.size(); i++)
        {
            //if(gameMapTerritoryList[i]->getTerritoryID() == inputSourceID
               //&& gameMapTerritoryList[i]->getTerritoryPlayerID() == playerID)
            //{
                //cout << "found source!" << endl;
                //source = gameMapTerritoryList[i];
            //}
        }

        for(int i = 0; i < gameMapTerritoryList.size(); i++)
        {
            //if(gameMapTerritoryList[i]->getTerritoryID() == inputDestID &&
               //gameMapTerritoryList[i]->getTerritoryPlayerID() == playerID && source->isAdjacent(dest))
            //{
                dest = gameMapTerritoryList[i];
                cout << "Adding territory "<< gameMapTerritoryList[i]->getTerritoryName() <<
                     " (" << gameMapTerritoryList[i]->getTerritoryID() << ") "<< "to defendList" << endl;
                defendList.push_back(dest);
                cout << "\nYour defend list will now look like this" <<  endl;
                printDefendList();
                cout << "\nAdding order to order list" << endl;
                orderList->addOrder(new AdvanceOrder::advance());

            //}

            //else if(gameMapTerritoryList[i]->getTerritoryID() == inputDestID &&
                    //gameMapTerritoryList[i]->getTerritoryPlayerID() != playerID && source->isAdjacent(dest))
            //{
                /*dest = gameMapTerritoryList[i];
                cout << "Adding territory "<< gameMapTerritoryList[i]->getTerritoryName() <<
                     " (" << gameMapTerritoryList[i]->getTerritoryID() << ") "<< "to attackList" << endl;
                attackList.push_back(dest);
                cout << "\nYour attack list will now look like this" <<  endl;
                printAttackList();
                cout << "\nAdding order to order list" << endl;
                orderList->addOrder(new AdvanceOrder::advance());*/
            //}

            /*else
            {
                cout << "Invalid choice! Territory does not belong to you or Source and Destination are not adjacent" << endl;
            }*/
        }
    }

    else if(orderName == "blockade"){
        cout << "Please enter territory ID:" << endl;
        cin >> id;

        cout << "\nAdding order to order list" << endl;
        orderList->addOrder(new blockade(*territoryList[id-1],*this));
    }

    else if(orderName == "airlift"){
        cout << "Please enter source territory ID:" << endl;
        cin >> sourceID;

        cout << "Please enter destination territory ID:" << endl;
        cin >> destID;

        cout << "Please enter amount:" << endl;
        cin >> amount;

        cout << "\nAdding order to order list" << endl;
        orderList->addOrder(new airlift(*territoryList[sourceID-1], *territoryList[destID-1], *this, amount));
    }

    else if(orderName == "negotiate"){
        cout << "Please enter a player's ID that you want to negotiate with: " << endl;
        cin >> pID;

        cout << "\nAdding order to order list" << endl;
        orderList->addOrder(new negotiate(*this, *gameEngine->getPlayers()[pID]));
    }

    else if(orderName == "bomb")
    {
        cout << "Please enter target territory ID:" << endl;
        cin >> id;

        cout << "Please enter target player ID:" << endl;
        cin >> pID;

        cout << "\nAdding order to order list" << endl;
        orderList->addOrder(new bomb(*territoryList[id-1], *gameEngine->getPlayers()[pID]));
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