#include "Map.h"
#include <iostream>

using namespace std;

//==========================
//          MAP
//==========================

/**
 * Default constructor
 */
Map::Map()
{
    pName = new string("");
}

/**
 * Copy constructor
 * @param orig
 */
Map::Map(const Map &orig)
{
    pName = new string(*orig.pName);
    for (auto &&t : orig.Territories)
    {
        Territories.push_back(new Territory(*t));
    }
}

/**
 * Destructor
 */
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

/**
 * Method that sets the map name
 * @param title
 */
void Map::setName(std::string title)
{
    *pName = title;
}

/**
 * Method that gets the map name
 * @return
 */
std::string Map::getName()
{
    return *pName;
}

/**
 * Boolean method that validate a given map by calling the uniqueContinentCheck()
 * & the isMapConnected() methods
 * @return
 */
bool Map::validate()
{
    // if the Continents or the Territories vectors are empty, the map is invalid
    if (Continents.empty() || Territories.empty())
    {
        cout << "\nSorry, your map is massively invalid!!!" << endl;
        return false;
    }
    // If Territories/Continents are not empty
    else if (Continents.size() > 1 || Territories.size() > 1)
    {
        for (int v = 0; v < Territories.size(); v++)
        {
            // if the adjacentTerritories vector is empty
            if (Territories[v]->adjTerritories.empty())
            {
                cout << "\nSorry, your map is massively invalid!!!" << endl;
                return false;
            }
        };
    }
    if (uniqueContinentCheck() && isMapConnected())
    {
        cout << "**************************************************" << endl;
        cout << "   \n          GREAT, YOUR MAP IS VALID!!!\n"
             << endl;
        cout << "**************************************************\n"
             << endl;

        return true;
    }
    else
    {
        cout << "Sorry, your map is massively invalid!!!" << endl;
        return false;
    }
};

/**
 * Boolean method that checks if a territory belongs to one continent only
 * Returns true if the condition is true. Otherwise, it returns false
 * @return
 */
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

/**
 * This boolean method checks if the map graph is connected by using DFS (depth-first search)
 * First, it checks that all the adjacent territories are in fact connected, by assigning each territory an id as well
 * as a "visitedT" flag.
 * Lastly, inside each continent, it checks that the adjacent territories (contained inside the territories vector)
 * are connected as well.
 * @return
 */
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
            for (int r = 0; r < visitedTerritories.size(); r++)
            {
                if (t == visitedTerritories[r].id && !visitedTerritories[r].visitedT)
                {
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
        visitedContinents.push_back(currentContinent);
    };
    startContId = Continents[0]->getContinentID();
    visitedContinents[0].visitedC = true;

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
                for (int g = 0; g < visitedContinents.size(); g++)
                {
                    if (adjcontinentId == visitedContinents[g].idC && !visitedContinents[g].visitedC)
                    {
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

/**
 * Method that gets a territory by id
 * @param territoryID
 * @return territory
 */
Territory *Map::getTerritoryById(int territoryID)
{
    for (int i = 0; i < Territories.size(); i++)
    {
        if (territoryID == Territories[i]->getTerritoryID())
        {
            return Territories[i];
        }
    }
}

/**
 * Method that gets a continent by id
 * @param continentId
 * @return continent
 */
Continent *Map::getContinentById(int continentId)
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

/**
 * Default constructor
 */
Territory::Territory()
{
    pTerritoryID = new int(1);
    pTerritoryName = new string("");
    pPlayerID = new int(); // only one player can own a territory
    pTerritoryName = new string("");
    pContinentName = new string("");
    pNumOfArmies = new int(0);
}

//setting our Territory object with a country, continent and armies value
/**
 * Constructor that sets our Territory object with a territoryID, name and continent name
 * @param territoryId
 * @param country
 * @param continent
 */
Territory::Territory(int territoryId, string country, string continent)
{
    *pTerritoryID = territoryId;
    *pTerritoryName = country;
    *pContinentName = continent;
}

/**
 * Copy constuctor
 * @param orig
 */
Territory::Territory(const Territory &orig)
{
    pTerritoryID = new int(*orig.pTerritoryID);
    pTerritoryName = new string(*orig.pTerritoryName);
    pTerritoryName = new string(*orig.pTerritoryName);
    pContinentName = new string(*orig.pContinentName);
    pPlayerID = new int(*orig.pPlayerID);
    pNumOfArmies = new int(*orig.pNumOfArmies);
    for (auto adjTerritory : orig.adjTerritories)
    {
        adjTerritories.push_back(adjTerritory);
    }
}

/**
 * Destructor
 */
Territory::~Territory()
{
    delete pTerritoryID;
    delete pPlayerID; // only one player can own a territory
    delete pTerritoryName;
    delete pContinentName;
    delete pNumOfArmies;

    for (auto adjTerritory : adjTerritories)
    {
        delete &adjTerritory;
    }
    adjTerritories.clear();
}

/**
 * Setter for the territoryID data member
 * @param territoryId
 */
void Territory::setTerritoryID(int territoryId)
{
    *pTerritoryID = territoryId;
}

/**
 * Getter for the territoryID data member
 * @return
 */
int Territory::getTerritoryID()
{
    return *pTerritoryID;
}

/**
 * Setter for the playerID
 * @param playerId
 */
void Territory::setTerritoryPlayerID(int playerId)
{
    *pPlayerID = playerId;
}

/**
 * Getter for the playerID
 * @return *pPlayerID
 */
int Territory::getTerritoryPlayerID()
{
    return *pPlayerID;
}

/**
 * Setter for the territoryName
 * @param territoryName
 */
void Territory::setTerritoryName(string territoryName)
{
    *pTerritoryName = territoryName;
}

/**
 * Getter for the territoryName
 * @return *pTerritoryName
 */
string Territory::getTerritoryName()
{
    return *pTerritoryName;
}

/**
 * Setter for the continentName
 * @param continent
 */
void Territory::setContinentName(string continent)
{
    *pContinentName = continent;
}

/**
 * Getter for the continent name
 * @return *pContinentName
 */
string Territory::getContinent()
{
    return *pContinentName;
}

/**
 * Setter for the continent ID
 * @param continentID
 */
void Territory::setContinentId(int continentID)
{
    continentId = continentID;
}

/**
 * Getter for the continent ID
 * @return continentId
 */
int Territory::getContinentId()
{
    return continentId;
}

/**
 * Setter for the number of armies
 * @param num
 */
void Territory::setNumOfArmies(int num)
{
    *pNumOfArmies = num;
}

/**
 * Getter for the number of armies
 * @return *pPlayerNumOfArmies
 */
int Territory::getNumOfArmies()
{
    return *pNumOfArmies;
}

/**
 * Method that prints territory information
 */
void Territory::displayTerritory()
{
    cout << "Player: " << getTerritoryPlayerID() << endl;
    cout << "Country: " << getTerritoryName() << endl;
    cout << "Continent : " << getContinent() << endl;
    cout << "Number of armies in this territory: " << getNumOfArmies() << endl;
}

//==========================
//        CONTINENT
//==========================

/**
 * Default constructor
 */
Continent::Continent()
{
    pContinentId = new int(1);
    pContinentName = new string("");
}

/**
 * Copy constructor
 */
Continent::Continent(const Continent &orig)
{
    pContinentId = new int(*orig.pContinentId);
    pContinentName = new string(*orig.pContinentName);

    for (auto territory : orig.territories)
    {
        territories.push_back(territory);
    }
}

/**
 * Destructor
 */
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

/**
 * Getter for the continent ID
 * @return *pContinentId
 */
int Continent::getContinentID()
{
    return *pContinentId;
}

/**
 * Setter for the continent ID
 * @param continentID
 */
void Continent::setContinentID(int continentID)
{
    *pContinentId = continentID;
}

/**
 * Getter for the continent name
 * @return
 */
string Continent::getContinentName()
{
    return *pContinentName;
}

/**
 * Setter for the continent name
 * @param continentName
 */
void Continent::setContinentName(string continentName)
{
    *pContinentName = continentName;
};

/**
 * Method that checks if a given territory is inside a continent
 * @param territory
 * @return
 */
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
