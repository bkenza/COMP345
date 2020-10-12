#pragma once
#include "Map.h"
#include "Orders.h"
#include "Cards.h"

class Player
{
    private:
        vector<Territory*> territoryList;
        vector<Cards*> playerDeck;
        vector<Cards*> playerHand;
        OrdersList orderList;
        vector<Territory*> attackList;
        vector<Territory*> defendList;

    public:
        Player();
        Player(vector<Territory*> tList, Deck pDeck, Hand pHand, OrdersList oList);
        ~Player();
        Player(const Player &obj);
        void setTerritoryList(vector<Territory*> tList);
        vector<Territory*> getTerritoryList();
        void setDeck(Deck deck);
        vector<Cards*> getDeck();
        void setHand(Hand hand);
        vector<Cards*> getHand();
        void setOrderList(OrdersList oList);
        OrdersList getOrderList();
        vector<Territory*> toDefend();
        vector<Territory*> toAttack();
        void printTerritoryList();
        void printAttackList();
        void printDefendList();
        void issueOrder(string orderName);
        void printHand();
        void printDeck();
};
