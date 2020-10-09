#pragma once
#include "Map.h"
#include "Orders.h"
#include "Cards.h"

class Player
{
    private:
        vector<Territory*>* territoryList;
        vector<Cards*>* cardList;
        OrdersList orderList;

    public:
        Player();
        Player(vector<Territory*> tList, vector<Cards*> cList, OrdersList oList);
        ~Player();
        Player(const Player &obj);
        void setTerritoryList(vector<Territory*> tList);
        vector<Territory*> getTerritoryList();
        void setCardList(vector<Cards*> cList);
        vector<Cards*> getCardList();

        void setOrderList(OrdersList oList);
        OrdersList getOrderList();
        vector<Territory*> toDefend();
        vector<Territory*> toAttack();
        void issueOrder(string orderName);
};
