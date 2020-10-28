#include "GameEngine.h"
#include "MapLoader.h"
#include <iostream>
#include <sstream>

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
