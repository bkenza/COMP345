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
    std::vector<Continent *> Continents;
    std::vector<Territory *> Territories;
    bool validate();
    bool uniqueContinentCheck();
    bool isMapConnected();
    void printMap(Map *);            // method to print the map (all territories and their adjacent territories)
    void setName(std::string title); // set the name of a given map
    std::string getName();           // get the name of a given map
    Territory getTerritoryById(int territoryID);
    Continent getContinentById(int continentId);
};
#endif

#ifndef TERRITORY_H
#define TERRITORY_H

class Territory
{
private:
    int *pTerritoryID;
    std::string *pTerritoryName;
    int *pPlayerID; // only one player can own a territory
    std::string *pContinentName;
    int *pPlayerNumOfArmies;
    int continentId;

public:
    Territory(); // constructor
    Territory(int territoryId, string country, string continent);
    Territory(const Territory &obj);
    virtual ~Territory(); // TODO: understand virtual
    void setTerritoryID(int territoryId);
    void setTerritoryPlayerID(int playerId);
    void setTerritoryName(string territoryName);
    std::string getTerritoryName();
    void setContinentName(string continent);
    void setContinentId(int continentID);
    void setNumOfArmies(int num);
    int getTerritoryID();
    int getTerritoryPlayerID();
    std::string getCountry();
    std::string getContinent();
    int getContinentId();
    int getNumOfArmies();
    void displayTerritory();
    std::vector<int> adjTerritories;
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
    Continent();                                 // default contructor
    Continent(const Continent &orig);            // copy contructor
    virtual ~Continent();                        // destructor TODO: does this need to be virtual
    int getContinentID();                        // method that returns the id of a continent
    void setContinentID(int continentID);        // method to set the id of a given continent
    std::string getContinentName();              // method that returns the name of a given continent
    void setContinentName(string continentName); // method that sets the name of a continent
    bool isInContinent(Territory *territory);
};

#endif