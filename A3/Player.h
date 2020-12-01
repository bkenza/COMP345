#pragma once
#include "Map.h"
#include "Orders.h"
#include "Cards.h"
#include "GameObservers.h"

class Hand;

class Player : public Subject
{
private:
    vector<Territory *> territoryList;
    Hand *playerHand;
    OrdersList orderList;
    int playerID;
    int numArmies;
    int phase;

public:
    Player();
    Player(vector<Territory *> tList, Hand hand, OrdersList oList);
    ~Player();
    Player(const Player &obj);
    void setTerritoryList(vector<Territory *> tList);
    vector<Territory *> getTerritoryList();
    void setHand(Hand *hand);
    Hand *getHand();
    void play(Deck *currentDeck, Cards *card);
    void setOrderList(OrdersList oList);
    OrdersList getOrderList();
    vector<Territory *> toDefend();
    vector<Territory *> toAttack();
    void printTerritoryList();
    void printAttackList();
    void printDefendList();
    void issueOrder(string orderName);
    void printHand();
    int getPlayerID();
    void setPlayerID(int playerId);
    void setNumOfArmies(int numOfArmy);
    int getNumOfArmies();
    int getPhase();
    void setPhase(int ph);
};
