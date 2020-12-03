#include "GameEngine.h"
#include "MapLoader.h"
#include "PlayerStrategies.h"
#include "Map.h"
#include "Orders.h"
#include "Cards.h"
#include <iostream>
#include <algorithm>
#include <random>

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
    phaseObserverOn = false;
    statsObserverOn = false;
    playerOrder;
    map = new Map();
    deck = new Deck();
    firstRound = true;
}

/**
 * Copy constructor
 **/
GameEngine::GameEngine(const GameEngine &obj)
{
    playerOrder = obj.playerOrder;
    phaseObserverOn = obj.phaseObserverOn;
    statsObserverOn = obj.statsObserverOn;
    numPlayers = obj.numPlayers;
    firstRound = true;
    map = obj.map;
    deck = obj.deck;
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

    playerOrder.clear();
}

/**
 * Method that starts the game, will use all the other methods
 **/
void GameEngine::startGame()
{
    // Ask the user to pick a map
    cout << "################################################### \n";
    cout << "               WELCOME TO WARZONE!                  \n";
    cout << "################################################### \n";
    cout << "\n \n";
    cout << "Here are the available maps: \n\n";

    getMaps();
    cout << "\nPlease select a map by entering the corresponding number: ";

    int mapSelected;
    cin >> mapSelected;

    while (mapSelected < 1 || mapSelected > mapList.size())
    {
        cin.clear();
        cin.ignore();
        cerr << "\nYikes! You have entered an invalid number, please try again: ";
        cin >> mapSelected;
    }

    cout << "\nCool! You have selected map number: " << mapSelected << endl; // maybe add a map selector method

    MapLoader* mapLoader;

    if (mapSelected <= 4) // Domination
    {
        // Load selected map
        mapLoader = new MapLoader();
    }

    else // Conquest
    {
        ConquestFileReader* conreader = new ConquestFileReader();
        mapLoader = new ConquestFileReaderAdapter(conreader);
    }

    map = mapLoader->MapReader("../Maps/" + mapSelector(mapSelected) + ".map");

    cout << "\nLet's see if the selected map is valid...\n\n";
    map->validate();

    // Select the number of players in the game(2 - 5 players)
    cout << "\nPlease enter the number of players (2-5): ";

    cin >> numPlayers;

    while (numPlayers < 2 || numPlayers > 5)
    {
        cin.clear();
        cin.ignore();
        cerr << "Yikes! You have entered an invalid number. The minimum number of players is 2 and the maximum is 5. Please try again: ";
        cin >> numPlayers;
    }

    cout << "The number of players is: " << numPlayers << endl;

    players[numPlayers];

    // Create all the players, assign a set of battle orders, create a deck of cards,and assign an empty hand of cards to each player.

    // Create a deck of cards
    deck = new Deck();
    deck->initializeDeck();
    int strategyType;

    // Creation of Players and adding them to the vector of players. Each player is given an id and an empty hand.
    for (int i = 0; i < numPlayers; i++)
    {
        Player *p = new Player(this);
        p->setPlayerID(i + 1);

        cout << "What strategy would you like to use for player " << p->getPlayerID() << endl;
        cout << "\n1. Human Player Strategy\n2. Aggressive Player Strategy\n3. Benevolent Player Strategy \n4. Neutral Player Strategy\n";

        cout << "Please enter the desired strategy: ";
        cin >> strategyType;

        // set player strategy type
        switch (strategyType)
        {
        case 1:
            p->setStrategy(new HumanPlayerStrategy());
            break;
        case 2:
            p->setStrategy(new AggressivePlayerStrategy());
            break;
        case 3:
            p->setStrategy(new BenevolentPlayerStrategy());
            break;
        case 4:
            p->setStrategy(new NeutralPlayerStrategy());
        }

        Hand *playerHand = new Hand();
        p->setHand(playerHand);
        //p->setMap(map);
        players.push_back(p);
        cout << "Player " << p->getPlayerID() << " created!\n";
    }

    mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());
    shuffle(std::begin(players), std::end(players), rng);

    cout << "\n************* PLAYER ORDER ***************\n";
    cout << "\n\nThe order of players is the following: \n";
    for (int k = 0; k < players.size(); k++)
    {
        cout << players[k]->getPlayerID() << endl;
    }

    // Select if Observers is on of off
    cout << "\nWould you like to have Phase Observers on? Enter y for Yes and n for No: ";

    string phaseObserverInput;
    cin >> phaseObserverInput;

    while (!(phaseObserverInput == "y" || phaseObserverInput == "n"))
    {
        cin.clear();
        cin.ignore();
        cerr << "Yikes! You have entered an invalid number. Please try again: ";
        cin >> phaseObserverInput;
    }

    cout << "Observers status: " << phaseObserverOn << endl;

    if (phaseObserverInput == "y")
    {
        for (int v = 0; v < numPlayers; v++)
        {
            GamePhaseObserver *phaseObserver = new GamePhaseObserver(players[v]);
        }
    }

    // Select id Observers is on of off
    cout << "\nWould you like to have Game Statistics Observers on? Enter y for Yes and n for No: ";

    string statsObserverInput;
    cin >> statsObserverInput;

    while (!(statsObserverInput == "y" || statsObserverInput == "n"))
    {
        cin.clear();
        cin.ignore();
        cerr << "Yikes! You have entered an invalid number. Please try again: ";
        cin >> statsObserverInput;
    }

    cout << "Observers status: " << statsObserverOn << endl;

    if (statsObserverInput == "y")
    {
        GameStatisticsObserver *gameStatisticsObserver = new GameStatisticsObserver(&(*this));
    }

    startupPhase(map);
    mainGameLoop();
}

/**
 * Method that gets a list of map names
 **/
void GameEngine::getMaps()
{
    for (int j = 0; j < mapList.size(); j++)
    {
        int mapNb = j + 1;
        cout << mapNb << ": " << mapList[j] << endl;
    }
}

/**
 * Getter for the current  players
 **/
vector<Player *> GameEngine::getPlayers()
{
    return players;
};

/**
 * setter for the current  players
 **/
void GameEngine::setPlayers(vector<Player *> p)
{
    players = p;
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
 * Setter for the chosen map
 **/
void GameEngine::setMap(Map *map)
{
    map = map;
}

/**
 * Getter for the chosen map
 **/
Map *GameEngine::getMap()
{
    return map;
}

/**
 * Getter for observers
 **/
bool GameEngine::getStatsObserverOn()
{
    return statsObserverOn;
}

/**
 * Setter for observers
 **/
void GameEngine::setStatsObserverOn(bool gameStatsObserverOn)
{
    gameStatsObserverOn = gameStatsObserverOn;
}

/**
 * Getter for observers
 **/
bool GameEngine::getPhaseObserverOn()
{
    return phaseObserverOn;
}

/**
 * Setter for observers
 **/
void GameEngine::setPhaseObserverOn(bool phaseObserverOn)
{
    phaseObserverOn = phaseObserverOn;
}

void GameEngine::setRound(bool round)
{
    firstRound = round;
}
bool GameEngine::getRound()
{
    return firstRound;
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
    int strategyType;
    bool changeStrategy;
    Player *currentPlayer;
    // Winner object is stored once game is over and we have a winner
    //Player* winner = NULL;

    //loop continues until only one of the players owns all territories in map
    while (numPlayers != 1)
    {
        //If a players territoryList size is 0, he/she is removed from the game because he/she no longer controls at least 1 territory
        //Iterating through GameEngine's list of players
        for (int i = 0; i < players.size(); i++)
        {
            if (players[i]->getTerritoryList()->empty())
            {
                Notify(); // Notify that player is eliminated and remove from view. Removal of player from list is taken care of by the observer
            }
        }

        if (!firstRound) // reinforcement phase is skipped during the first round
        {
            cout << "Would you like to change player strategies? [0/1]";
            cin >> changeStrategy;

            if (changeStrategy)
            {
                for (int i = 0; i < numPlayers; i++)
                {
                    currentPlayer = players[i];

                    cout << "Select the appropriate strategy for player" << currentPlayer->getPlayerID() << endl;
                    cout
                        << "1. Human Player Strategy\n 2. Aggressive Player Strategy\n 3. Benevolent Player Strategy \n 4. Neutral Player Strategy";

                    cin >> strategyType;

                    // set player strategy type
                    switch (strategyType)
                    {
                    case 1:
                        currentPlayer->setStrategy(new HumanPlayerStrategy());
                        break;
                    case 2:
                        currentPlayer->setStrategy(new AggressivePlayerStrategy());
                        break;
                    case 3:
                        currentPlayer->setStrategy(new BenevolentPlayerStrategy());
                        break;
                    case 4:
                        currentPlayer->setStrategy(new NeutralPlayerStrategy());
                    }
                }
            }

            // Reinforcement Phase
            reinforcementPhase();
        }

        // Issuing Orders Phase
        issueOrdersPhase();

        // Orders Execution Phase
        executeOrdersPhase();

        int listSize = players.size();

        for (int i = 0; i < listSize; i++)
        {
            players[i]->clearFriends();
        }

        firstRound = false;
    }
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
    for (int i = 0; i < players.size(); i++)
    {

        players[i]->setPhase("Reinforcement");
        players[i]->Notify();
        cout << "Player: " << players[i]->getPlayerID() << "'s old Reinforcement Pool: " << players[i]->getReinforcementPool();
        // if (number of territories owned) / 3 is less than 3, assigns 3 to the player reinforcement pool
        if (((players[i]->getTerritoryList()->size()) / 3) < 3) // removed round
        {
            cout << "| Player: " << players[i]->getPlayerID() << "'s updated Reinforcement Pool: ";
            players[i]->setReinforcementPool(players[i]->getReinforcementPool() + 3);
            cout << players[i]->getReinforcementPool() << endl;
        }

        //check if players owned number of territories matches a continent that hold n amount of territories in order to gain control bonus
        else if (players[i]->ownAllTerritoryInContinent())
        {
            cout << "| Player: " << players[i]->getPlayerID() << "'s updated Reinforcement Pool: ";
            players[i]->setReinforcementPool(players[i]->getReinforcementPool() + 10);
            cout << players[i]->getReinforcementPool() << endl;
        }

        else
        {
            cout << "| Player: " << players[i]->getPlayerID() << "'s updated Reinforcement Pool: ";
            players[i]->setReinforcementPool(players[i]->getReinforcementPool() + ((players[i]->getTerritoryList()->size()) / 3)); // removed round
            cout << players[i]->getReinforcementPool() << endl;
        }
    }
}

// each player make orders and place them in their order list, if an order is a card it calls play method that will play a  card from hand
void GameEngine::issueOrdersPhase()
{
    //deploy -> put armies in a territory

    /*advance -> moves a specified number of armies between adjacent territories, if its a player territory, armies get transferred
     *           to that territory, if its an enemy territory, an attack happens between the 2 territories
    */

    //bomb -> destroy half of the armies located on an opponent's territory that is adjacent to one of player's territory

    //blockade -> triple number of armies on one of player's current territory and make it a neutral territory (cannot be attacked?)

    //airlift -> advance armies from user territory to any other territory

    //negotiate -> prevent attacks between current and another player until end of turn

    for (int i = 0; i < players.size(); i++)
    {
        players[i]->setPhase("Issue Orders");
        players[i]->Notify();
        int pID = players[i]->getPlayerID();
        vector<Cards *> currentPlayerHandCards = players[i]->getHand()->HandCards;
        string type;
        string answer;
        bool isHuman = (players[i]->getStrategy()->getStrategyType() == "human");

        if (isHuman)
        {
            while (answer != "n")
            {
                cout << "Player " << pID << ", it is your turn to make a move! Make an order of your choice!\n"
                     << endl;
                cout << "Input your desired order here: ";
                cin >> type;

                // If input is advance or deploy it calls issueOrder
                if (type == "advance" || type == "deploy")
                {
                    players[i]->issueOrder(type);
                }

                // If input is any of these it will loop through player's hands to see if card exists and play it as well as add it
                // to orders list
                else if (type == "bomb" || type == "blockade" || type == "airlift" || type == "negotiate")
                {
                    cout << currentPlayerHandCards.size() << endl;

                    // If hand is empty output error message
                    if (currentPlayerHandCards.size() == 0)
                    {
                        cout << "Invalid order! Your hand is empty!!" << endl;
                    }

                    // looping through player's hand to find appropriate card
                    for (int j = 0; j < currentPlayerHandCards.size(); j++)
                    {
                        if (currentPlayerHandCards[j]->getCardType() == type)
                        {
                            players[i]->play(deck, currentPlayerHandCards[j]);
                        }

                        else
                        {
                            cout << "Such a card does not exist in your hand!" << endl;
                        }
                    }
                }

                else
                {
                    cout << "Invalid order!" << endl;
                }

                // asks user if he/she desires to issue a new order, if no, his or her turn ends and goes to next player in queue
                cout << "Would you like to issue another order? Type y for YES or n for NO" << endl;
                cin >> answer;
                if (answer == "no")
                {
                    break;
                }
                cout << "\n"
                     << endl;
            }
        }
        else if(!isHuman)
        {
            cout << "Computer Player is trying to deploy" << endl;
            players[i]->issueOrder("deploy"); // issue deploy order

            cout << "Computer Player is trying to advance" << endl;
            players[i]->issueOrder("advance"); // issue advance order

            int count = 0;
            while (currentPlayerHandCards.size() > 0 && count < 3) // for all computer players, we will play two cards from hand
            {
                players[i]->play(deck, currentPlayerHandCards[i]);
            }
        }
    }
}

// Executing orders for each player in a round robin fashion based on the order priority 1:deploy, 2:airlift, 3:blockade, 4: all others
void GameEngine::executeOrdersPhase()
{
    int beforeTerritoryListSize;
    int afterTerritoryListSize;
    // 1:deploy NEED TO CHECK IF REINFORCEMENT POOL IS EMPTY OTHERWISE CANNOT EXECUTE OTHER ORDERS
    for (int i = 0; i < players.size(); i++)
    {
        players[i]->setPhase("Execute Orders DEPLOY (1st priority)");
        players[i]->Notify();
        beforeTerritoryListSize = players[i]->getTerritoryList()->size();
        OrdersList *currentPlayerOrdersList = players[i]->getOrderList();

        // If player's order list is empty do not display
        if (players[i]->getOrderList()->getOrdersListSize() != 0)
        {
            players[i]->setPhase("Execute Orders DEPLOY (1st priority)");
            players[i]->Notify();
        }

        // looping through player's order list
        for (int j = 0; j < currentPlayerOrdersList->getOrdersListSize(); j++)
        {
            if (currentPlayerOrdersList->getOrder(j)->getLabel() == "deploy")
            {
                //execute deploy actions here
                currentPlayerOrdersList->getOrder(j)->execute();
                currentPlayerOrdersList->deleteOrder(j + 1);
            }
        }
        afterTerritoryListSize = players[i]->getTerritoryList()->size();
        if (afterTerritoryListSize - beforeTerritoryListSize)
        { // if the player conquered at least one territory, they can draw a card
            deck->draw(players[i]->getHand());
        }
    }

    // 2: airlift
    for (int i = 0; i < players.size(); i++)
    {
        if (players[i]->getOrderList()->getOrdersListSize() != 0)
        {
            players[i]->setPhase("Execute Orders: AIRLIFT (2nd priority)");
            players[i]->Notify();
        }

        OrdersList *currentPlayerOrdersList = players[i]->getOrderList();

        for (int j = 0; j < currentPlayerOrdersList->getOrdersListSize(); j++)
        {
            if (currentPlayerOrdersList->getOrder(j)->getLabel() == "airlift")
            {
                //execute airlift actions here
                currentPlayerOrdersList->getOrder(j)->execute();
                currentPlayerOrdersList->deleteOrder(j + 1);
            }
        }
    }

    // 3: blockade
    for (int i = 0; i < players.size(); i++)
    {
        if (players[i]->getOrderList()->getOrdersListSize() != 0)
        {
            players[i]->setPhase("Execute Orders: BLOCKADE (3rd priority)");
            players[i]->Notify();
        }

        OrdersList *currentPlayerOrdersList = players[i]->getOrderList();

        for (int j = 0; j < currentPlayerOrdersList->getOrdersListSize(); j++)
        {
            if (currentPlayerOrdersList->getOrder(j)->getLabel() == "blockade")
            {
                //execute blockade actions here
                currentPlayerOrdersList->getOrder(j)->execute();
                currentPlayerOrdersList->deleteOrder(j + 1);
            }
        }
    }

    // 4: rest of the orders executed in this block
    for (int i = 0; i < players.size(); i++)
    {
        if (players[i]->getOrderList()->getOrdersListSize() != 0)
        {
            players[i]->setPhase("Execute Orders: executing the rest according to their order in the list");
            players[i]->Notify();
        }

        OrdersList *currentPlayerOrdersList = players[i]->getOrderList();

        for (int j = 0; j < currentPlayerOrdersList->getOrdersListSize(); j++)
        {
            if (currentPlayerOrdersList->getOrder(j)->getLabel() == "advance")
            {
                //execute advance actions here
                currentPlayerOrdersList->getOrder(j)->execute();
                currentPlayerOrdersList->deleteOrder(j + 1);
            }

            else if (currentPlayerOrdersList->getOrder(j)->getLabel() == "bomb")
            {
                //execute bomb actions here
                currentPlayerOrdersList->getOrder(j)->execute();
                currentPlayerOrdersList->deleteOrder(j + 1);
            }

            else if (currentPlayerOrdersList->getOrder(j)->getLabel() == "negotiate")
            {
                //execute negotiate actions here
                currentPlayerOrdersList->getOrder(j)->execute();
                currentPlayerOrdersList->deleteOrder(j + 1);
            }
        }
    }
}
//+++++++++++++++++++++++++++++++
//    Part 2: Startup Phase
//+++++++++++++++++++++++++++++++

/**
 * Method that assigns number of armies at the beginning of the game depending on the amount of players in the game
 */
void GameEngine::startupPhase(Map *map)
{

    //setRandomPlayerOrder();
    assignTerritories(map);

    int A;

    switch (numPlayers)
    {
    case 2:
        A = 40;
        break;
    case 3:
        A = 35;
        break;
    case 4:
        A = 30;
        break;
    case 5:
        A = 25;
        break;
    };

    // set the number of armies
    for (int p = 0; p < players.size(); p++)
    {
        (players[p])->setReinforcementPool(A);
    }

    cout << "\n************* PLAYER ARMY ASSIGNMENT ***************\n";
    cout << "Each player has been assigned " << A << " armies" << endl;
}

/**
 * Method that sets player orders randomly
 **/
void GameEngine::setRandomPlayerOrder()
{
    for (int n = 0; n < numPlayers; n++)
    {
        playerOrder.push_back(n + 1);
    }
    mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());
    shuffle(std::begin(playerOrder), std::end(playerOrder), rng);

    cout << "\n************* PLAYER ORDER ***************\n";
    cout << "\n\nThe order of players is the following: \n";
    for (int k = 0; k < numPlayers; k++)
    {
        cout << playerOrder[k] << endl;
    }
}

/**
 * Method that assigns territories to players in a round-robin fashion
 **/
void GameEngine::assignTerritories(Map *map)
{

    Player *roundPlayer;
    vector<int> AdjTerritories;
    Territory *adjTerritory;

    cout << "\n************* TERRITORY ASSIGNMENT ***************\n";

    for (int t = 0; t < map->Territories.size(); t++)
    {
        roundPlayer = players[t % numPlayers];
        map->Territories[t]->setTerritoryPlayerID(roundPlayer->getPlayerID());
        roundPlayer->getTerritoryList()->push_back(map->Territories[t]);
        roundPlayer->getDefendList()->push_back(map->Territories[t]); // add territories to defendList

        cout << "\nTerritory " << map->Territories[t]->getTerritoryName() << " (" << map->Territories[t]->getTerritoryID() << ") "
             << " was assigned to Player " << roundPlayer->getPlayerID() << endl;
    }

    for (int c = 0; c < players.size(); c++)
    {
        for (int d = 0; d < players[c]->getTerritoryList()->size(); d++)
        {
            vector<int> AdjTerritories = map->getTerritoryById((*players[c]->getTerritoryList())[d]->getTerritoryID())->adjTerritories;

            for (int x = 0; x < AdjTerritories.size(); x++)
            {

                adjTerritory = map->getTerritoryById(AdjTerritories[x]);

                if (adjTerritory->getTerritoryPlayerID() != players[c]->getPlayerID())
                {
                    players[c]->getAttackList()->push_back(adjTerritory);
                }
            }
        }
    }
}

/**
 * Getter for player ID
 * @param id
 * @return
 */
Player *GameEngine::getPlayerByID(int id)
{
    int listSize = players.size();

    for (int i = 0; i < listSize; i++)
    {
        if (id == players[i]->getPlayerID())
        {
            return players[i];
        }
    }

    cout << "Player not found!\n"
         << endl;
    return nullptr;
}

/**
 * Getting for deck
 * @return deck
 */
Deck *GameEngine::getDeck()
{
    return deck;
}