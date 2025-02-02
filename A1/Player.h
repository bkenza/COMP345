#pragma once
#include "Map.h"
#include "Orders.h"
#include "Cards.h"

class Hand;

class Player
{
    private:
        vector<Territory*> territoryList;
        Hand *playerHand;
        OrdersList orderList;
        int playerID;
    public:
        Player();
        Player(vector<Territory*> tList, Hand hand, OrdersList oList);
        ~Player();
        Player(const Player &obj);
        void setTerritoryList(vector<Territory*> tList);
        vector<Territory*> getTerritoryList();
        void setHand(Hand *hand);
        Hand *getHand();
        void play(Deck *currentDeck, Cards *card);
        void setOrderList(OrdersList oList);
        OrdersList getOrderList();
        vector<Territory*> toDefend();
        vector<Territory*> toAttack();
        void printTerritoryList();
        void printAttackList();
        void printDefendList();
        void issueOrder(string orderName);
        void printHand();
        int getPlayerID();
        void setPlayerID(int );
};
