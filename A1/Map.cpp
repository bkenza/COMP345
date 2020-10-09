#include "Map.h"
#include <iostream>

using namespace std;

//==========================
//          MAP
//==========================

// Default constructor
Map::Map()
{
    pName = new string("");
}

// Copy constructor
Map::Map(const Map &orig)
{
    pName = new string(*orig.pName);
    for (auto &&t : orig.Territories)
    {
        Territories.push_back(new Territory(*t));
    }
}

// Destructor
Map::~Map()
{
    delete pName;
    for (auto t : Territories)
    {
        delete t;
    }
    Territories.clear();
    for (auto c : Continents)
    {
        delete c;
    }
    Continents.clear();
}

// Set map pName
void Map::setName(std::string title)
{
    *pName = title;
}

// Get map pName
std::string Map::getName()
{
    return *pName;
}

//TODO: create this method
bool validate()
{
    //validate method
    return true;
};

//TODO: create a printMap method
void printMap(Map *map)
{
    // print the current map
    // Print territories
}

Territory Map::getTerritoryById(int territoryID)
{
    for (int i = 0; i < Territories.size(); i++)
    {
        if (Territories[i]->getTerritoryID() == territoryID)
        {
            return *Territories[i];
        }
    }
}

//---------------------------
//     Territory
//---------------------------

//default constructor
Territory::Territory()
{
    pTerritoryID = new int(1);
    pTerritoryName = new string("");
    pPlayerID = new int(); // only one player can own a territory
    pTerritoryName = new string("");
    pContinentName = new string("");
    pPlayerNumOfArmies = new int(0);
}

// TODO: check if the syntax is right aka do we need to add "new"???????
//setting our Territory object with a country, continent and armies value
Territory::Territory(int territoryId, string country, string continent)
{
    *pTerritoryID = territoryId;
    *pTerritoryName = country;
    *pContinentName = continent;
}

// Copy constructor
// TODO: if this does not work, add a pointer
Territory::Territory(const Territory &orig)
{
    pTerritoryID = new int(*orig.pTerritoryID);
    pTerritoryName = new string(*orig.pTerritoryName);
    pTerritoryName = new string(*orig.pTerritoryName);
    pContinentName = new string(*orig.pContinentName);
    pPlayerID = new int(*orig.pPlayerID);
    pPlayerNumOfArmies = new int(*orig.pPlayerNumOfArmies);
    for (auto adjTerritory : orig.adjTerritories)
    {
        adjTerritories.push_back(adjTerritory);
    }
}

//Destructor to call finalize() and free unwanted resources
Territory::~Territory()
{
    delete pTerritoryID;
    delete pPlayerID; // only one player can own a territory
    delete pTerritoryName;
    delete pContinentName;
    delete pPlayerNumOfArmies;

    for (auto adjTerritory : adjTerritories)
    {
        delete &adjTerritory;
    }
    adjTerritories.clear();
}

//Setter for territoryID data member
void Territory::setTerritoryID(int territoryId)
{
    *pTerritoryID = territoryId;
}

int Territory::getTerritoryID()
{
    return *pTerritoryID;
    ;
}

// Setter for playerID datamember
void Territory::setTerritoryPlayerID(int playerId)
{
    *pPlayerID = playerId;
}

// Getter for playerID datamember
int Territory::getTerritoryPlayerID()
{
    return *pPlayerID;
}

// Setter for pTerritoryName data member
void Territory::setTerritoryName(string territoryName)
{
    *pTerritoryName = territoryName;
}

// Getter for pTerritoryName data member
string Territory::getTerritoryName()
{
    return *pTerritoryName;
}

//Setter for pContinentName data member
void Territory::setContinentName(string continent)
{
    *pContinentName = continent;
}

//Getter for pContinent data member
string Territory::getContinent()
{
    return *pContinentName;
}

//Setter for pNumOfArmy data member
void Territory::setNumOfArmies(int num)
{
    *pPlayerNumOfArmies = num;
}

//Getter for pNumOfArmy data member
int Territory::getNumOfArmies()
{
    return *pPlayerNumOfArmies;
}

//Display territory information
void Territory::displayTerritory()
{
    //cout << "Displaying information for Territory " << get << endl;
    cout << "Player: " << getTerritoryPlayerID() << endl;
    //    cout << "Country: " << getCountry() << endl;
    cout << "Continent : " << getContinent() << endl;
    cout << "Number of armies in this territory: " << getNumOfArmies() << endl;
}

//-------------------------
//        CONTINENT
//-------------------------

// default contructor
Continent::Continent()
{
    pContinentId = new int(1);
    pContinentName = new string("");
}

// Copy constructor
// TODO: if this does not work, add a pointer
Continent::Continent(const Continent &orig)
{
    pContinentId = new int(*orig.pContinentId);
    pContinentName = new string(*orig.pContinentName);

    for (auto territory : orig.territories)
    {
        territories.push_back(territory);
    }
}

// Destructor
Continent::~Continent()
{
    delete pContinentId;
    delete pContinentName;
    for (auto t : territories)
    {
        delete t;
    }
    territories.clear();
}

// Getter for the continent id
int Continent::getContinentID()
{
    return *pContinentId;
}

// Setter for the continent id
void Continent::setContinentID(int continentID)
{
    *pContinentId = continentID;
}

// Getter for the continent id
string Continent::getContinentName()
{
    return *pContinentName;
}

void Continent::setContinentName(string continentName)
{
    *pContinentName = continentName;
};

bool Continent::isInContinent(Territory *territory)
{
    for (auto t : territories)
    {
        if (t == territory)
            return true;
        return false;
    }
    return false;
}
