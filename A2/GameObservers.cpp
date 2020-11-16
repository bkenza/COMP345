#include "GameObservers.h"
using namespace std;
#include <iostream>
#include <algorithm>

//******** Observer Class *************

/**
 * Default constructor
 **/
Observer::Observer(){};

/**
 * Destructor
 **/
Observer::~Observer(){};

/**
 * Copy construcor
 **/
Observer::Observer(const Observer &obj){
    
}

/**
 * Assignment operator
 **/
//Observer& Observer::operator=(const Observer &obj)
//{
//    //TODO:
//}

//********* Subject class ***********

/**
 * Default constructor
 **/
Subject::Subject(){
};

/**
 * Destructor
 **/
Subject::~Subject(){
    for (auto q : observerList)
    {
        delete q;
    }
    observerList.clear();
};

/**
 * Copy construcor
 **/
Subject::Subject(const Subject &obj)
{};

/**
 * Assignment operator
 **/
//Subject& Subject::operator=(const Subject &obj)
//{
//    //TODO:
//}

void Subject::TurnOn(Observer *obs)
{
    cout << "Observer turned on!" << endl;
    observerList.push_back(obs);
}

void Subject::TurnOff(Observer *obs)
{
    cout << "Observer turned off!" << endl;
    observerList.erase(remove(observerList.begin(), observerList.end(), obs), observerList.end());
}

void Subject::Notify()
{
    cout << "Notify was called!" << endl;
    for (int i = 0; i < observerList.size(); i++)
    {
        observerList[i]->Update();
    }
}


//************ Phase Observer *******************

/**
 * Default constructor
 **/
GamePhaseObserver::GamePhaseObserver(){
    //default
};

/**
 * Parametrized constructor
 **/
GamePhaseObserver::GamePhaseObserver(Player *p) {
    player = p;
    player->TurnOn(this);
}

GamePhaseObserver::GamePhaseObserver(const GamePhaseObserver& orig)
{
    player = new Player(*orig.player);
}

GamePhaseObserver& GamePhaseObserver::operator=(const GamePhaseObserver &obj) {
    if (this != &obj)
    {
        delete player;
        player = new Player(*obj.player);
    }
    return *this;
}

GamePhaseObserver::~GamePhaseObserver()
{
    player->TurnOff(this);
    delete player;
}

void GamePhaseObserver::Update()
{
    cout << "\n********************** PHASE OBSERVER **************************************\n";
    cout << "Player " << player->getPlayerID() << ":  " << player->getPhase() << " phase\n";
    cout << "****************************************************************************\n";
}

//********** Game Stats Observer ************

/**
 * Default constructor
 **/
GameStatisticsObserver::GameStatisticsObserver(){
    //default
};

/**
 * Parametrized constructor
 **/
GameStatisticsObserver::GameStatisticsObserver(GameEngine *g)
{
    gameEngine = g;
    gameEngine->TurnOn(this);
    Update();
}

/**
 * Copy constructor
 **/
GameStatisticsObserver::GameStatisticsObserver(const GameStatisticsObserver &orig)
{
    gameEngine = new GameEngine(*orig.gameEngine);
}

/**
 * Assignment operator
 **/
GameStatisticsObserver &GameStatisticsObserver::operator=(const GameStatisticsObserver &obj)
{
    if (this != &obj)
    {
        delete gameEngine;
        gameEngine = new GameEngine(*obj.gameEngine);
    }
    return *this;
}

/**
 * Destructor
 **/
GameStatisticsObserver::~GameStatisticsObserver()
{
    gameEngine->TurnOff(this);
    delete gameEngine;
}

/**
 * Function that outputs information about the current game statistics 
 * & checks if players are to be ejected from the game
 * It also announces a winner if there is one (the game is then terminated)
 **/
void GameStatisticsObserver::Update()
{
    vector<Territory *> territories = gameEngine->getMap()->Territories;
    int totalNumTerritories = territories.size();
    int conqueredTerritories = 0;
    Territory *currentTerritory;

    cout << "\n********************** STATISTICS OBSERVER **************************************\n\n";
    cout << "------------ Current Map Stats Table ----------------\n";
    cout << "TERRITORIES\n";
    cout << "-------------------------------------------------\n";
    cout << "Territory      Player      Armies      Continent";
    cout << "-------------------------------------------------\n";

    for (int w = 0; w < totalNumTerritories; w++)
    {
        currentTerritory = territories[w];
        cout << currentTerritory->getTerritoryName() << "      " << currentTerritory->getTerritoryPlayerID() << "      " << currentTerritory->getNumOfArmies() << "      " << currentTerritory->getContinent() << endl;
    }

    // Calculate percentage of world domination
    cout << "------------ World domination table! % of map conquered per player ----------------\n";
    cout << "--------------------------------\n";
    cout << "Player      % Map conquered";
    cout << "--------------------------------\n";
    for (int p = 0; p < gameEngine->getPlayers().size(); p++)
    {
        conqueredTerritories = gameEngine->getPlayers()[p]->getTerritoryList().size();
        float territoryRatio = float(conqueredTerritories) / totalNumTerritories;

        // check if any player has 0 territories
        if (conqueredTerritories == 0)
        {
            cout << "Player " << gameEngine->getPlayers()[p]->getPlayerID() << " has been ejected from the game!";
            (gameEngine->getPlayers()).erase((gameEngine->getPlayers().begin() + p)); // remove ejected player from t
        }

        cout << gameEngine->getPlayers()[p]->getPlayerID() << "      " << territoryRatio << "%\n";
        cout << "-------------------------------------------------\n";
    }

    // Check if any player has conquered the whole map. If so, announce player as winner and terminate game.
    for (int p = 0; p < gameEngine->getPlayers().size(); p++)
    {
        conqueredTerritories = gameEngine->getPlayers()[p]->getTerritoryList().size();
        if (conqueredTerritories = totalNumTerritories)
        {
            cout << "Player " << gameEngine->getPlayers()[p]->getPlayerID() << " has won the game!" << endl;
            cout << "Thank you for playing Warzone (comp345 edition)!" << endl;
            exit(EXIT_SUCCESS);
        }
    }
}
