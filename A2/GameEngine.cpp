#include "GameEngine.h"
#include "MapLoader.h"
#include <iostream>
#include <algorithm>
#include <random>

using namespace std;

//#########################
//     GAME ENGINE
//#########################

//TODO: type checking ??
//TODO: check number of cards in deck
//TODO: each class must have an assignment operator

/**
 * Default constructor
 **/
GameEngine::GameEngine()
{
    numPlayers = int(0);
    phaseObserverOn = false;
    statsObserverOn = false;
    playerTurn = int(0);
    playerOrder;
}

/**
 * Copy constructor
 **/
GameEngine::GameEngine(const GameEngine &obj)
{
    playerOrder = obj.playerOrder;
    playerTurn = obj.playerTurn;
    phaseObserverOn = obj.phaseObserverOn;
    statsObserverOn = obj.statsObserverOn;
    numPlayers = obj.numPlayers;
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
        cerr << "\nYikes! You have entered an invalid number, please try again: ";
        cin >> mapSelected;
    }

    cout << "\nCool! You have selected map number: " << mapSelected << endl; // maybe add a map selector method

    // Load selected map
    MapLoader *mapLoader = new MapLoader();
    Map *map = mapLoader->MapReader("../Maps/" + mapSelector(mapSelected) + ".map");

    cout << "\nLet's see if the selected map is valid...\n\n";
    map->validate();

    // Select the number of players in the game(2 - 5 players)
    cout << "\nPlease enter the number of players (2-5): ";

    cin >> numPlayers;

    while (numPlayers < 1 || numPlayers > 5)
    {
        cerr << "Yikes! You have entered an invalid number. The minimum number of players is 2 and the maximum is 5. Please try again: ";
        cin >> numPlayers;
    }

    cout << "The number of players is: " << numPlayers << endl;

    // Turn on/off any of the observers
    // TODO: implement part 5 first

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
        cout << "Player " << p->getPlayerID() << " created!\n";
    }

    // Select id Observers is on of off
    cout << "\nWould you like to have Phase Observers on? Enter 1 for Yes and 0 for No: ";

    cin >> phaseObserverOn;

    while (0 > phaseObserverOn || phaseObserverOn > 1)
    {
        cerr << "Yikes! You have entered an invalid number. Please try again: ";
        cin >> phaseObserverOn;
    }

    cout << "Observers status: " << phaseObserverOn << endl;

    if(phaseObserverOn == 1) {
        for(int v = 0; v < numPlayers; v++) {
            GamePhaseObserver *phaseObserver = new GamePhaseObserver(players[v]);
        }
    }

    // Select id Observers is on of off
    cout << "\nWould you like to have Game Statistics Observers on? Enter 1 for Yes and 0 for No: ";

    cin >> statsObserverOn;

    while (0 > statsObserverOn || statsObserverOn > 1)
    {
        cerr << "Yikes! You have entered an invalid number. Please try again: ";
        cin >> statsObserverOn;
    }

    cout << "Observers status: " << statsObserverOn << endl;

    if(statsObserverOn == 1){
        GameStatisticsObserver* gameStatisticsObserver =  new GameStatisticsObserver(&(*this));
    }

    startupPhase(map);
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

vector<int> GameEngine::getPlayerOrder()
{
    return playerOrder;
}

void GameEngine::setPlayerOrder(vector<int> pOrder)
{
    playerOrder = pOrder;
}

void GameEngine::setPlayerTurn(int pTurn)
{
    playerTurn = pTurn;
}
int GameEngine::getPlayerTurn()
{
    return playerTurn;
}

/**
 * Method to select the right map depending on user input
 **/
string GameEngine::mapSelector(int mapNumber)
{
    return mapList[mapNumber - 1];
}

//+++++++++++++++++++++++++++++++
//    Part 2: Startup Phase
//+++++++++++++++++++++++++++++++

void GameEngine::startupPhase(Map *map)
{

    setRandomPlayerOrder();
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
        (players[p])->setNumOfArmies(A);
        //TODO: change this to reinforcement pool
    }

    cout << "\n************* PLAYER ARMY ASSIGNMENT ***************\n";
    cout << "Each player has been assigned " << A << " armies";
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

    cout << "\n************* TERRITORY ASSIGNMENT ***************\n";

    for (int t = 0; t < map->Territories.size(); t++)
    {
        roundPlayer = players[t % numPlayers];
        roundPlayer->getTerritoryList().push_back(map->Territories[t]);

        cout << "\nTerritory " << map->Territories[t]->getTerritoryName() << " was assigned to Player " << roundPlayer->getPlayerID() << endl;
    }
}