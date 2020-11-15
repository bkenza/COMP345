#include "GameEngine.h"
#include "MapLoader.h"
#include "Map.h"
#include "Orders.h"
#include "Cards.h"
#include <iostream>

using namespace std;

//#########################
//     GAME ENGINE
//#########################

/**
 * Default constructor
 **/
GameEngine::GameEngine()
{
    numPlayers = int(0);
    observersOn = false;
    mapList;
    players;
    deck;
}

/**
 * Copy constructor
 **/
GameEngine::GameEngine(const GameEngine &obj)
{
}

/**
 * Destructor
 **/
GameEngine::~GameEngine()
{
    for (auto p : players)
    {
        delete p;
    }
    players.clear();
}

/**
 * Method that starts the game, will use all the other methods
 **/
void GameEngine::startGame()
{
    // Ask the user to pick a map
    cout << "################################################### \n";
    cout << "               WELCOME TO WARZONE!                    ";
    cout << "################################################### \n";

    cout << "Here are the available maps: ";

    getMaps();
    cout << "Please select a map by entering the corresponding number: \n"
         << endl;

    int mapSelected;
    cin >> mapSelected;

    while (mapSelected < 1 || mapSelected > mapList->size())
    {
        cout << "Yikes! You have entered an invalid number, please try again.";
        cin >> mapSelected;
    }

    cout << "Cool! You have selected map number: " << mapSelected << endl; // maybe add a map selector method

    // Select the number of players in the game(2 - 5 players)
    cout << "Please enter the number of players (2-5): \n"
         << endl;

    cin >> numPlayers;

    while (mapSelected < 1 || mapSelected > mapList->size())
    {
        cout << "Yikes! You have entered an invalid number. The minimum number of players is 2 and the maximum is 5. Please try again.";
        cin >> mapSelected;
    }

    cout << "The number of players is: " << numPlayers << endl;

    // Turn on/off any of the observers
    // TODO: implement part 5 first

    // Load selected map
    MapLoader *mapLoader = new MapLoader();
    Map *map = mapLoader->MapReader("../Maps/" + mapSelector(mapSelected) + ".map");

    map->validate();

    players[numPlayers];

    // Create all the players, assign a set of battle orders, create a deck of cards,and assign an empty hand of cards to each player.

    // Create a deck of cards
    deck = new Deck();
    deck->initializeDeck(); //TODO: change intiailize method to have the right nb od

    // Creation of Players and adding them to the vector of players. Each player is given an id and an empty hand.
    for (int i = 0; i < numPlayers; i++)
    {
        Player *p = new Player();
        p->setPlayerID(i + 1);
        Hand *playerHand = new Hand();
        p->setHand(playerHand);
        players.push_back(p);
    }
}

/**
 * Method that gets a list of map names
 **/
void GameEngine::getMaps()
{

    cout << "List of existing maps: \n"
         << endl;

    for (int i = 0; i < mapList->size(); i++)
    {
        cout << i + 1 + ": " << mapList[i] << endl;
    }
}

/**
 * Getter for number of players
 **/
int GameEngine::getNumPlayers()
{
    return numPlayers;
}

/**
 * Setter for number of players
 **/
void GameEngine::setNumPlayers(int nbOfPlayers)
{
    numPlayers = nbOfPlayers;
}

/**
 * Getter for observers
 **/
bool GameEngine::getObserversOn()
{
    return observersOn;
}

/**
 * Setter for observers
 **/
void GameEngine::setObserversOn(bool observersOn)
{
    observersOn = observersOn;
}

/**
 * Method to select the right map depending on user input
 **/
string GameEngine::mapSelector(int mapNumber)
{
    return mapList[mapNumber - 1];
}

/*
 * round robin fashion 3 phases -> reinfrocement, issuing order, orders execution
 */
void GameEngine::mainGameLoop()
{
    // Winner object is stored once game is over and we have a winner
    Player* winner = NULL;

    //loop continues until only one of the players owns all territories in map
    while(numPlayers != 1)
    {
        if(numPlayers == 1)
        {
            winner = players[numPlayers];
        }

        //If a players territoryList size is 0, he/she is removed from the game because he/she no longer controls at least 1 territory
        //Iterating through GameEngine's list of players
        for(int i = 0; i < players.size(); i++)
        {
            if(players[i]->getTerritoryList().empty())
            {
                players.erase(players.begin()+i);
                numPlayers--;
            }
        }

        // Reinforcement Phase
        reinforcementPhase();

        // Issuing Orders Phase
        issueOrdersPhase();

        // Orders Execution Phase
        executeOrdersPhase();
    }

    cout << "THE WINNER IS PLAYER"<< winner->getPlayerID() << endl;
}

/*
 * Players are given a number of armies that depends on the number of territories
 * they own, (# of territories owned divided by 3, rounded down). If the player owns all the territories of an
 * entire continent, the player is given a number of armies corresponding to the continent’s control bonus
 * value. In any case, the minimal number of reinforcement armies per turn for any player is 3. These armies
 * are placed in the player’s reinforcement pool.
 */
void GameEngine::reinforcementPhase()
{
    for(int i = 0; i < players.size(); i++)
    {
        // if (number of territories owned) / 3 is less than 3, assigns 3 to the player reinforcement pool
        if(((players[i]->getTerritoryList().size()) / 3) < 3) // removed round
        {
            players[i]->setReinforcementPool(players[i]->getReinforcementPool() + 3);
        }

        //check if players owned number of territories matches a continent that hold n amount of territories in order to gain control bonus
        else if(players[i]->ownAllTerritoryInContinent())
        {
            players[i]->setReinforcementPool(players[i]->getReinforcementPool() + 10);
        }

        else
        {
            players[i]->setReinforcementPool(players[i]->getReinforcementPool() + ((players[i]->getTerritoryList().size()) / 3)); // removed round
        }
    }
}

// each player make orders and place them in their orderlist
void GameEngine::issueOrdersPhase()
{
    //deploy -> put armies in a territory

    /*advance -> moves a specified number of armies between adjacent territories, if its a player territory, armies get transfered
     *           to that territory, if its an enemy territory, an attack happens between the 2 territories
    */

    //bomb -> destory half of the armies located on an opponent's territory that is adjacent to one of player's territory

    //blockade -> triple number of armies on one of player's current territory and make it a neutral territory (cannot be attacked?)

    //airlift ->

    //negotiate -> prevent attacks between current and another player until end of turn

    for(int i = 0; i < players.size(); i++)
    {
        Player* currentPlayer = players[i];
        int pID = players[i]->getPlayerID();
        vector<Cards*> currentPlayerHandCards = currentPlayer->getHand()->HandCards;
        string type;
        string answer;

        while(answer != "y")
        {
            cout << "Player "<< pID << "it is now your turn to make a move! Make an order of your choice!"<< endl;
            cin >> type;

            if(type == "advance" || type == "deploy")
            {
                currentPlayer->issueOrder(type);
            }

            else
            {
                for(int j = 0; j < currentPlayerHandCards.size(); j++)
                {
                    if(currentPlayerHandCards[j]->getCardType() == type)
                    {
                        currentPlayer->play(deck, currentPlayerHandCards[j]);
                    }

                    else
                    {
                        cout << "Such a card does not exist in your deck!" << endl;
                    }
                }
            }


            cout << "Would you like to issue another order? Type y for YES or n for NO" << endl;
            cin >> answer;

            /*if(ans == "y")
            {
                break;
            }*/
        }
    }
}

// Executing orders for each player in a round robin fashion based on the order priority 1:deploy, 2:airlift, 3:blockade, 4: all others
void GameEngine::executeOrdersPhase()
{
    // 1:deploy NEED TO CHECK IF REINFORCEMENT POOL IS EMPTY OTHERWISE CANNOT EXECUTE OTHER ORDERS
    for(int i = 0; i < players.size(); i++)
    {
        OrdersList* currentPlayerOrdersList = players[i]->getOrderList();

        for(int j = 0; j < currentPlayerOrdersList->getOrdersListSize(); j++)
        {
            if(currentPlayerOrdersList->getOrder(j)->getLabel() == "deploy")
            {
                //execute deploy actions here
                currentPlayerOrdersList->getOrder(j)->execute();
            }
        }
    }

    // 2: airlift
    for(int i = 0; i < players.size(); i++)
    {
        OrdersList* currentPlayerOrdersList = players[i]->getOrderList();

        for(int j = 0; j < currentPlayerOrdersList->getOrdersListSize(); j++)
        {
            if(currentPlayerOrdersList->getOrder(j)->getLabel() == "airlift")
            {
                //execute airlift actions here
                currentPlayerOrdersList->getOrder(j)->execute();
            }
        }
    }

    // 3: blockade
    for(int i = 0; i < players.size(); i++)
    {
        OrdersList* currentPlayerOrdersList = players[i]->getOrderList();

        for(int j = 0; j < currentPlayerOrdersList->getOrdersListSize(); j++)
        {
            if(currentPlayerOrdersList->getOrder(j)->getLabel() == "blockade")
            {
                //execute blockade actions here
                currentPlayerOrdersList->getOrder(j)->execute();
            }
        }
    }

    // 4: rest of the orders executed in this block
    for(int i = 0; i < players.size(); i++)
    {
        OrdersList* currentPlayerOrdersList = players[i]->getOrderList();

        for(int j = 0; j < currentPlayerOrdersList->getOrdersListSize(); j++)
        {
            if(currentPlayerOrdersList->getOrder(j)->getLabel() == "advance")
            {
                //execute advance actions here
                currentPlayerOrdersList->getOrder(j)->execute();
            }

            if(currentPlayerOrdersList->getOrder(j)->getLabel() == "bomb")
            {
                //execute bomb actions here
                currentPlayerOrdersList->getOrder(j)->execute();
            }

            if(currentPlayerOrdersList->getOrder(j)->getLabel() == "negotiate")
            {
                //execute negotiate actions here
                currentPlayerOrdersList->getOrder(j)->execute();
            }
        }
    }
}