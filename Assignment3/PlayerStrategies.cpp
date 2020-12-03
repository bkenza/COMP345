#include "PlayerStrategies.h"

//++++++++++++++++++++++++++++
//   Human Player Strategy
//++++++++++++++++++++++++++++

string HumanPlayerStrategy::getStrategyType()
{
    return "human";
}

/**
 * Method that returns a vector containing the defend list of the current player
 * */
vector<Territory *> HumanPlayerStrategy::toDefend(Player *player)
{
    return *(player->getDefendList());
}

/**
 * Method that returns a vector containing the attack list of the current player
 * */
vector<Territory *> HumanPlayerStrategy::toAttack(Player *player)
{
    return *(player->getAttackList());
}

void HumanPlayerStrategy::issueOrder(Player *player, string orderName)
{
    if (orderName != "deploy" && player->getReinforcementPool() > 0)
    {
        cout << "Invalid Order! You can select orders other than deploy only when you have"
             << " no armies in the reinforcement pool!" << endl;
    }

    if (orderName == "deploy")
    {
        while (player->getReinforcementPool() > 0)
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
            } while (amount > player->getReinforcementPool() || amount < 1);

            player->setReinforcementPool(player->getReinforcementPool() - amount);

            Territory *targetTerritory = player->getGE()->getMap()->getTerritoryById(targetTerritoryID);

            player->getOrderList()->addOrder(new deploy(*targetTerritory, *player, amount));

            return;
        }
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

        Territory *sourceTerritory = player->getGE()->getMap()->getTerritoryById(sourceTerritoryID);
        Territory *targetTerritory = player->getGE()->getMap()->getTerritoryById(targetTerritoryID);

        do
        {
            cout << "\nInput the number of armies you want to advance!" << endl;
            cin.clear();
            cin.ignore();
            cin >> amount;

        } while (amount > sourceTerritory->getNumOfArmies() || amount < 1);

        sourceTerritory->setNumOfArmies(sourceTerritory->getNumOfArmies() - amount);
        player->getOrderList()->addOrder(new AdvanceOrder::advance(*sourceTerritory, *targetTerritory, *player, amount));
    }

    else if (orderName == "blockade")
    {
        int targetTerritoryID;

        cout << "\nPlease enter territory ID:" << endl;
        cin >> targetTerritoryID;

        Territory *targetTerritory = player->getGE()->getMap()->getTerritoryById(targetTerritoryID);
        player->getOrderList()->addOrder(new blockade(*targetTerritory, *player));
    }

    else if (orderName == "airlift")
    {
        int sourceTerritoryID;
        int targetTerritoryID;
        int amount;

        cout << "\nPlease enter source territory ID:" << endl;
        cin >> sourceTerritoryID;

        cout << "\nPlease enter destination territory ID:" << endl;
        cin >> targetTerritoryID;

        Territory *sourceTerritory = player->getGE()->getMap()->getTerritoryById(sourceTerritoryID);
        Territory *targetTerritory = player->getGE()->getMap()->getTerritoryById(targetTerritoryID);

        do
        {
            cout << "\nPlease enter amount:" << endl;
            cin >> amount;

        } while (amount > sourceTerritory->getNumOfArmies() || amount < 1);

        sourceTerritory->setNumOfArmies(sourceTerritory->getNumOfArmies() - amount);
        player->getOrderList()->addOrder(new airlift(*sourceTerritory, *targetTerritory, *player, amount));
    }

    else if (orderName == "negotiate")
    {
        int targetPlayerID;

        cout << "Please enter a player's ID that you want to negotiate with: " << endl;
        cin >> targetPlayerID;

        Player *targetPlayer = player->getGE()->getPlayerByID(targetPlayerID);

        player->getOrderList()->addOrder(new negotiate(*targetPlayer, *player));
    }

    else if (orderName == "bomb")
    {
        int targetTerritoryID;

        cout << "Please enter target territory ID:" << endl;
        cin >> targetTerritoryID;

        Territory *targetTerritory = player->getGE()->getMap()->getTerritoryById(targetTerritoryID);

        player->getOrderList()->addOrder(new bomb(*targetTerritory, *player));
    }
}

//+++++++++++++++++++++++++++++++++
//   Aggressive Player Strategy
//+++++++++++++++++++++++++++++++++

string AggressivePlayerStrategy::getStrategyType()
{
    return "aggressive";
}

vector<Territory *> AggressivePlayerStrategy::toDefend(Player *player)
{
    return *(player->getDefendList()); // holds only the strongest territory
}

vector<Territory *> AggressivePlayerStrategy::toAttack(Player *player)
{
    return *(player->getAttackList());
}

void AggressivePlayerStrategy::issueOrder(Player *player, string orderName)
{

    Territory *territory;
    int randomTerritoryId;
    Territory *strongestTerr = (*player->getTerritoryList())[0];
    int maxTerritories = 0;
    Territory *adjTerrToAttack;
    bool firstRound = true; //change
    int numArmies = player->getReinforcementPool();
    vector<Territory *> newDefendList;

    if (orderName == "deploy")
    {

        cout << "\nDeployment phase!" << endl;

        // find the strongest territory
        for (int z = 0; z < player->getTerritoryList()->size(); z++)
        {
            territory = (*player->getTerritoryList())[z];
            if (territory->getNumOfArmies() > maxTerritories)
            {
                maxTerritories = territory->getNumOfArmies();
                strongestTerr = territory;
            }
        }

        if (firstRound)
        {
            //assign rest of armies to random strongest territory
            if (numArmies > 0)
            {
                randomTerritoryId = rand() % ((player->getTerritoryList()->size()));
                strongestTerr = (*player->getTerritoryList())[randomTerritoryId];
                newDefendList.push_back(strongestTerr);
                player->setDefendList(newDefendList); //add strongest territory to defendList
            }
        }

        player->getOrderList()->addOrder(new deploy(*strongestTerr, *player, numArmies)); // add deployment order
        cout << "\nYou are tyring to deploy  " << numArmies << " armies on your strongest Territory " << strongestTerr->getTerritoryName() << endl;

        if (orderName == "advance")
        {
            if (strongestTerr->getNumOfArmies() <= 1)
            {
                cout << "Sorry, your strongest territory does not have enough armies to advance. Better luck next time!" << endl;
            }
            else
            {
                //look for an adjacent territory to our strongest
                vector<int>(adjTerritories) = (*player->getGE()->getMap()->getTerritoryById(strongestTerr->getTerritoryID())).adjTerritories;
                adjTerrToAttack = player->getGE()->getMap()->getTerritoryById(adjTerritories[0]);
                bool hasAdjacent = false;
                for (int i = 0; i < adjTerritories.size(); i++)
                {
                    if ((player->getGE()->getMap()->getTerritoryById(adjTerritories[i])->getTerritoryPlayerID()) != player->getPlayerID())
                    {
                        hasAdjacent = true;
                        adjTerrToAttack = player->getGE()->getMap()->getTerritoryById(adjTerritories[i]);
                        break;
                    }
                    if (!hasAdjacent)
                    {
                        cout << "Sorry, there are no territories to attack!" << endl;
                        return;
                    }
                    cout << "Currently attacking " << adjTerrToAttack->getTerritoryName() << " using "
                         << player->getGE()->getMap()->getTerritoryById(strongestTerr->getTerritoryID())->getNumOfArmies() - 1 << "armies" << endl;
                }

                strongestTerr->setNumOfArmies(1);
                player->getOrderList()->addOrder(new AdvanceOrder::advance(*strongestTerr, *adjTerrToAttack, *player, adjTerrToAttack->getNumOfArmies() - 1));
            }
        }
    }

    else if (orderName == "blockade")
    {
        cout << "You are an agressive player, you do not want to issue this order as you will lose your strongest territory." << endl;
    }

    else if (orderName == "airlift") //ensures that all armies are aggregated in one country, the strongest one.
    {
        Territory *currentTerritory;

        for (int q = 0; q < player->getTerritoryList()->size(); q++)
        {
            currentTerritory = (*player->getTerritoryList())[q];
            if (currentTerritory != strongestTerr && currentTerritory->getNumOfArmies() > 0)
            {
                player->getOrderList()->addOrder(new airlift(*currentTerritory, *strongestTerr, *player, currentTerritory->getNumOfArmies()));
            }
        }
    }

    else if (orderName == "bomb")
    {
        int targetTerritoryID;

        do
        {
            targetTerritoryID = rand() % (player->getGE()->getMap()->Territories.size());
        } while (player->getPlayerID() != player->getGE()->getMap()->getTerritoryById(targetTerritoryID)->getTerritoryPlayerID());

        Territory *targetTerritory = player->getGE()->getMap()->getTerritoryById(targetTerritoryID);

        player->getOrderList()->addOrder(new bomb(*targetTerritory, *player));
    }
}

//+++++++++++++++++++++++++++++++++
//   Benevolent Player Strategy
//+++++++++++++++++++++++++++++++++
string BenevolentPlayerStrategy::getStrategyType()
{
    return "benevolent";
}

vector<Territory *> BenevolentPlayerStrategy::toAttack(Player *player)
{
    return *(player->getAttackList());
}

vector<Territory *> BenevolentPlayerStrategy::toDefend(Player *player)
{
    return *(player->getDefendList());
}

void BenevolentPlayerStrategy::issueOrder(Player *player, string orderName)
{
    Territory *territory;
    vector<Territory *> weakestTerritories;
    int minTerritories = 0;
    int randomTerritoryId;
    Territory *adjTerrToAttack;
    bool firstRound = true; //change
    int numArmies = player->getReinforcementPool();
    int sumArmies = 0;
    int averageNumArmies = 0;
    int numArmiesToWeakest = 0;

    if (orderName == "deploy")
    {
        cout << "\nDeployment phase!" << endl;

        // find the weakest territory
        for (int p = 0; p < player->getTerritoryList()->size(); p++)
        {
            sumArmies += player->getGE()->getMap()->getTerritoryById((*player->getTerritoryList())[p]->getTerritoryID())->getNumOfArmies();
        }

        averageNumArmies = sumArmies / player->getTerritoryList()->size();

        // find the weakest territories
        for (int z = 0; z < player->getTerritoryList()->size(); z++)
        {
            territory = (*player->getTerritoryList())[z];
            if (territory->getNumOfArmies() <= averageNumArmies)
            {
                weakestTerritories.push_back(territory);
            }
        }

        // adding armies to weakest territories in round robin
        numArmiesToWeakest = numArmies / weakestTerritories.size();

        for (int u = 0; u < weakestTerritories.size(); u++)
        {
            if (u = weakestTerritories.size() - 1)
            {
                numArmiesToWeakest = numArmies;
            }

            territory = weakestTerritories[u];
            player->getOrderList()->addOrder(new deploy(*territory, *player, numArmiesToWeakest));
            numArmies = numArmies - numArmiesToWeakest;
            player->setReinforcementPool(numArmies); // remove the deployed armies from reinforcement pool

            cout << "\nYou deployed" << numArmiesToWeakest << " armies on one of your weakest Territories " << territory->getTerritoryName() << endl;
        }
    }

    else if (orderName == "advance") //benevolent player does not attack
    {
        cout << "You are a benevolent player, you do not have to worry about advancing into enemy territories";
    }

    else if (orderName == "blockade")
    {
        int targetTerritoryID;

        do
        {
            targetTerritoryID = rand() % (player->getGE()->getMap()->Territories.size());
        } while (player->getPlayerID() != player->getGE()->getMap()->getTerritoryById(targetTerritoryID)->getTerritoryPlayerID());

        Territory *targetTerritory = player->getGE()->getMap()->getTerritoryById(targetTerritoryID);

        player->getOrderList()->addOrder(new blockade(*targetTerritory, *player));
        cout << "You are a benevolent player, you do not have to worry about blockade hehe" << endl;
    }

    else if (orderName == "airlift")
    {
        cout << "You are a benevolent player, you do not have to worry about airlift hehe" << endl;
    }

    else if (orderName == "bomb") // benevolent player does not attack
    {
        cout << "You are a benevolent player, you do not have to worry about bombing your enemy hehe" << endl;
    }
}

//+++++++++++++++++++++++++++++++++
//   Neutral Player Strategy
//+++++++++++++++++++++++++++++++++

string NeutralPlayerStrategy::getStrategyType()
{
    return "neutral";
}

vector<Territory *> NeutralPlayerStrategy::toDefend(Player *player)
{
    return *(player->getDefendList());
}

vector<Territory *> NeutralPlayerStrategy::toAttack(Player *player)
{
    return *(player->getAttackList());
}

void NeutralPlayerStrategy::issueOrder(Player *player, string orderName)
{
    cout << "You are a neutral player, you cannot issue a(n) " << orderName << "order" << endl;
}
