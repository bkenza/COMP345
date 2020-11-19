#pragma once
#include <vector>
#include <string>
#include <GameObservers.h>

using std::vector;
using std::string;

class Map;
class Territory;
class Hand;
class Deck;
class Cards;
class OrdersList;

class Player : public Subject
{
    private:
        vector<Territory*> territoryList;
        Hand* playerHand;
        OrdersList* orderList;
        int playerID;
        int reinforcementPool;
        vector<Territory*> attackList;
        vector<Territory*> defendList;
        GameEngine* gameEngine;
        string phase;
        vector<int> friendlyPlayers; // Player who you cannot attack for the remainder of the turn

    public:
        Player();
        Player(GameEngine*);
        Player(vector<Territory*> tList, Hand* hand, OrdersList* oList);
        ~Player();
        Player(const Player& obj);
        vector<Territory*>* getTerritoryList();
        //void setMap(Map* map);
        //Map *getMap();
        void setHand(Hand* hand);
        Hand *getHand();
        void play(Deck* currentDeck, Cards* card);
        void setOrderList(OrdersList* oList);
        OrdersList* getOrderList();
        vector<Territory*> toDefend();
        vector<Territory*> toAttack();
        void printTerritoryList();
        void printAttackList();
        void printDefendList();
        void issueOrder(string orderName);
        //void printHand();
        int getPlayerID();
        void setPlayerID(int);
        void setReinforcementPool(int n);
        int getReinforcementPool();
        bool ownAllTerritoryInContinent();
        string getPhase();
        void setPhase(string ph);
        void addFriendly(int);
        bool canAttack(int);
        void clearFriends();
};
