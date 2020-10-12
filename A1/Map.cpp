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
bool Map::validate()
{
    if(Continents.empty() || Territories.empty()) {
        cout << "\nSorry, your map is massively invalid!!!" << endl;
        return false;
    }
    else if(Continents.size() > 1 || Territories.size() > 1) {
        for(int v=0; v < Territories.size(); v++) {
            if(Territories[v]->adjTerritories.empty()) {
                cout << "\nSorry, your map is massively invalid!!!" << endl;
                return false;
            }
        };
    }
    if (uniqueContinentCheck() && isMapConnected())
    {
        cout << "**************************************************"<<endl;
        cout << "   \n          GREAT, YOUR MAP IS VALID!!!\n" << endl;
        cout << "**************************************************\n"<<endl;

        return true;
    }
    else{
        cout << "Sorry, your map is massively invalid!!!" << endl;
        return false;
    }
};

bool Map::uniqueContinentCheck()
{
    Territory *currentTerritory = new Territory();
    int continentCount = 0;
    for (auto t : Territories)
    {
        continentCount = 0;
        *currentTerritory = *t;
        for (auto c : Continents)
        {
            for (auto ter : c->territories)
            {
                if (ter->getTerritoryID() == currentTerritory->getTerritoryID())
                {
                    continentCount++;
                }
            }
        }
        if (continentCount != 1)
        {
            return false;
        }
    }
    return true;
};

// Thus method checks if the graph is connected by using DFS (depth-first search).
// TODO: explain more
bool Map::isMapConnected()
{
    bool isConnected = true; // map is a connected graph
    int poppedId;

    struct visitedTerritory
    {
        int id = 0;
        bool visitedT = false;
    };
    vector<visitedTerritory> visitedTerritories;
    vector<int> stackOfIds;
    visitedTerritory currentTerritory;
    Territory *poppedTerritory = new Territory();
    int test;

    for (int i = 0; i < Territories.size(); i++)
    {
        currentTerritory.id = Territories[i]->getTerritoryID();
        currentTerritory.visitedT = false;
        visitedTerritories.push_back(currentTerritory);
    };

    int startId = Territories[0]->getTerritoryID();
    for (auto v : visitedTerritories)
    {
        if (v.id == startId)
        {
            v.visitedT = true;
        };
    }
    stackOfIds.push_back(startId);

    while (!stackOfIds.empty())
    {
        poppedId = stackOfIds.back();
        stackOfIds.pop_back();

        *poppedTerritory = *getTerritoryById(poppedId);

        for (auto t : poppedTerritory->adjTerritories)
        {
            for(int r=0; r < visitedTerritories.size(); r++) {
                if (t == visitedTerritories[r].id && !visitedTerritories[r].visitedT) {
                    visitedTerritories[r].visitedT = true;
                    stackOfIds.push_back(t);
                }
            }
        }
    }

    for (auto x : visitedTerritories)
    {
        if (!x.visitedT)
        {
            isConnected = false;
        }
    }

    // Continents
    struct visitedContinent
    {
        int idC = 0;
        bool visitedC = false;
    };
    vector<visitedContinent> visitedContinents;
    vector<int> stackOfContIds;
    visitedContinent currentContinent;
    int startContId;
    Continent *poppedContinent = new Continent();
    int adjcontinentId;
    Territory *adjTerritory;

    for (int j = 0; j < Continents.size(); j++)
    {
        currentContinent.idC = Continents[j]->getContinentID();
//        currentContinent.visitedC = false;
        visitedContinents.push_back(currentContinent);
    };
    startContId = Continents[0]->getContinentID();
    visitedContinents[0].visitedC = true;
//    for (auto z : visitedContinents)
//    {
//        if (z.idC == startContId)
//        {
//            z.visitedC = true;
//        };
//    }
    stackOfContIds.push_back(startContId);

    while (!stackOfContIds.empty())
    {
        poppedId = stackOfContIds.back();
        stackOfContIds.pop_back();

        *poppedContinent = *getContinentById(poppedId);

        for (auto k : poppedContinent->territories)
        {
            for (auto b : k->adjTerritories)
            {
                adjTerritory = getTerritoryById(b);
                adjcontinentId = adjTerritory->getContinentId();
                for (int g=0; g < visitedContinents.size(); g++) {
                    if (adjcontinentId == visitedContinents[g].idC && !visitedContinents[g].visitedC) {
                        visitedContinents[g].visitedC = true;
                        stackOfContIds.push_back(adjcontinentId);
                    }
                }
            }
        }
    }

    for (auto q : visitedContinents)
    {
        if (!q.visitedC)
        {
            isConnected = false;
        }
    }
    return isConnected;
}

//TODO: create a printMap method
void printMap(Map *map)
{
    // print the current map
    // Print territories
}

Territory* Map::getTerritoryById(int territoryID)
{
    for (int i = 0; i < Territories.size(); i++)
    {
        if (territoryID == Territories[i]->getTerritoryID())
        {
            return Territories[i];
        }
    }
}

Continent* Map::getContinentById(int continentId)
{
    for (int i = 0; i < Continents.size(); i++)
    {
        if (Continents[i]->getContinentID() == continentId)
        {
            return Continents[i];
        }
    }
}

//==========================
//     Territory
//==========================

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
}

// Setter for playerID data member
void Territory::setTerritoryPlayerID(int playerId)
{
    *pPlayerID = playerId;
}

// Getter for playerID data member
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

void Territory::setContinentId(int continentID)
{
    continentId = continentID;
}

int Territory::getContinentId()
{
    return continentId;
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
        cout << "Country: " << getTerritoryName() << endl;
    cout << "Continent : " << getContinent() << endl;
    cout << "Number of armies in this territory: " << getNumOfArmies() << endl;
}

//==========================
//        CONTINENT
//==========================

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
