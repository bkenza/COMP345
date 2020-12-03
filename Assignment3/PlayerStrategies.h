#ifndef ASSIGNMENT3_PLAYERSTRATEGIES_H
#define ASSIGNMENT3_PLAYERSTRATEGIES_H

// #include "Player.h"
#include "GameEngine.h"
#include "Orders.h"
#include "Map.h"

class Player;

class PlayerStrategy
{
public:
    virtual vector<Territory *> toAttack(Player *player) = 0;
    virtual vector<Territory *> toDefend(Player *player) = 0;
    virtual void issueOrder(Player *player, string orderName) = 0;
    virtual string getStrategyType() = 0;
};

class HumanPlayerStrategy : public PlayerStrategy
{
public:
    vector<Territory *> toAttack(Player *player);
    vector<Territory *> toDefend(Player *player);
    void issueOrder(Player *player, string orderName);
    string getStrategyType();
};

class AggressivePlayerStrategy : public PlayerStrategy
{
public:
    vector<Territory *> toAttack(Player *player);
    vector<Territory *> toDefend(Player *player);
    void issueOrder(Player *player, string orderName);
    string getStrategyType();
};

class BenevolentPlayerStrategy : public PlayerStrategy
{
public:
    vector<Territory *> toAttack(Player *player);
    vector<Territory *> toDefend(Player *player);
    void issueOrder(Player *player, string orderName);
    string getStrategyType();
};

class NeutralPlayerStrategy : public PlayerStrategy
{
public:
    vector<Territory *> toAttack(Player *player);
    vector<Territory *> toDefend(Player *player);
    void issueOrder(Player *player, string orderName);
    string getStrategyType();
};

#endif //ASSIGNMENT3_PLAYERSTRATEGIES_H
