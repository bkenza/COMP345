#ifndef MAP_H
#define MAP_H

#include <iostream>
#include <cstdlib>
#include <vector>

using namespace std;
class Continent;
class Territory;

class Map
{
private:
    std::string *pName; // name/title of a given map
public:
    Map();                // default constructor
    Map(const Map &orig); // Copy constructor
    virtual ~Map();       // destructor
    std::vector<Continent *> Continents; // Vector containing pointers to continents
    std::vector<Territory *> Territories; // Vector containing pointers to territories
    bool validate(); // method that validates a given map
    bool uniqueContinentCheck(); // method that checks if a territory is inside one continent only
    bool isMapConnected(); // method that checks if a map is a connected graph
    void setName(std::string title); // set the name of a given map
    std::string getName();           // get the name of a given map
    Territory *getTerritoryById(int territoryID); // get a territory by id
    Continent *getContinentById(int continentId); // get a continent by id
};

#endif

#ifndef TERRITORY_H
#define TERRITORY_H

class Territory
{
private:
    int *pTerritoryID; // pointer to a territory id
    std::string *pTerritoryName; // pointer to a territory name
    int *pPlayerID; // only one player can own a territory
    std::string *pContinentName; // pointer to a continent name
    int *pPlayerNumOfArmies; // pointer to the number of armies a player owns
    int continentId; // continent id

public:
    Territory(); // default constructor
    Territory(int territoryId, string country, string continent); // constructor with parameters
    Territory(const Territory &obj); // copy constructor
    virtual ~Territory(); // // destructor
    void setTerritoryID(int territoryId); // setter for the territory id
    void setTerritoryPlayerID(int playerId); // setter for the player id
    void setTerritoryName(string territoryName); // setter for the territory name
    std::string getTerritoryName(); // getter for the territory name
    void setContinentName(string continent); // setter for the continent name
    void setContinentId(int continentID); // setter for the continent id
    void setNumOfArmies(int num); // setter for the number of armies
    int getTerritoryID(); // getter for the territory id
    int getTerritoryPlayerID(); // getter for they player if
    std::string getContinent(); // getter for the continent name
    int getContinentId(); // getter for the continent id
    int getNumOfArmies(); // getter for the number of armies
    void displayTerritory(); // method that displays territory info
    std::vector<int> adjTerritories; // vector containing ids of adjacent territories
    bool isAdjacent(Territory* dest);
};
#endif

#ifndef CONTINENT_H
#define CONTINENT_H

class Continent
{
private:
    int *pContinentId;
    std::string *pContinentName;

public:
    std::vector<Territory *> territories;        //vector holding all territories in continent
    Continent();                                 // default constructor
    Continent(const Continent &orig);            // copy constructor
    virtual ~Continent();                        // destructor TODO: does this need to be virtual
    int getContinentID();                        // method that returns the id of a continent
    void setContinentID(int continentID);        // method to set the id of a given continent
    std::string getContinentName();              // method that returns the name of a given continent
    void setContinentName(string continentName); // method that sets the name of a continent
    bool isInContinent(Territory *territory); // method that checks if a given territory is inside a continent
};

#endif
