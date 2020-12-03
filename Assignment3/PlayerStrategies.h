#ifndef ASSIGNMENT3_PLAYERSTRATEGIES_H
#define ASSIGNMENT3_PLAYERSTRATEGIES_H

#include "GameEngine.h"
#include "Orders.h"
#include "Map.h"

class Player;

class PlayerStrategy
{
public:
    virtual vector<Territory *> toAttack(Player *player) = 0; // Method that returns the toAttack list of the current player
    virtual vector<Territory *> toDefend(Player *player) = 0; // Method that returns the toDefend list of the current player
    virtual void issueOrder(Player *player, string orderName) = 0; // Method that issues orders
    virtual string getStrategyType() = 0;
};

class HumanPlayerStrategy : public PlayerStrategy //focused on strongest territory and attack
{
public:
    vector<Territory *> toAttack(Player *player);
    vector<Territory *> toDefend(Player *player);
    void issueOrder(Player *player, string orderName);
    string getStrategyType();
};

class AggressivePlayerStrategy : public PlayerStrategy //focuses on weakest territories
{
public:
    vector<Territory *> toAttack(Player *player);
    vector<Territory *> toDefend(Player *player);
    void issueOrder(Player *player, string orderName);
    string getStrategyType();
};

class BenevolentPlayerStrategy : public PlayerStrategy //focuses on spectating
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
