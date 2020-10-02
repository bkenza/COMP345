#include "Territory.h"
#include <iostream>
#include <typeinfo>

using namespace TerritoryNamespace;

//default constructor
Territory::Territory() {}

//setting our Territory object with a country, continent and armies value
Territory::Territory(int territoryId, int playerId, string country, string continent, int num)
{
    this->territoryID = territoryId;
    this->playerID = playerId;
    this->pCountry = &country;
    this->pContinent = &continent;
    this->playerNumOfArmies = num;
}

Territory::Territory(const Territory &obj)
{
    *pCountry = *obj.pCountry;
    *pContinent = *obj.pContinent;
    //*playerNumOfArmies = *obj.playerNumOfArmies;
}

//Destructor to call finalize() and free unwanted resources
Territory::~Territory() = default;

//Setter for territoryID datamember
void Territory::setTerritoryID(int territoryId)
{
    this->territoryID == territoryId;
}

int Territory::getTerritorryID()
{
    return territoryID;
    ;
}

//Setter for playerID datamember
void Territory::setTerritoryPlayerID(int playerId)
{
    this->playerID = playerId;
}

int Territory::getTerritoryPlayerID()
{
    return playerID;
}

//Setter for pCountry data member
void Territory::setCountry(string country)
{
    this->pCountry = &country;
}

//Getter for pCountry data member
string Territory::getCountry()
{
    return *pCountry;
}

//Setter for pContinent data member
void Territory::setContinent(string continent)
{
    this->pContinent = &continent;
}

//Getter for pContinent data member
string Territory::getContinent()
{
    return *pContinent;
}

//Setter for pNumOfArmy data member
void Territory::setNumOfArmies(int num)
{
    this->playerNumOfArmies = num;
}

//Getter for pNumOfArmy data member
int Territory::getNumOfArmies()
{
    return playerNumOfArmies;
}

//Display territory information
void Territory::displayTerritory()
{
    //cout << "Displaying information for Territory " << get << endl;
    cout << "Player: " << getTerritoryPlayerID() << endl;
    cout << "Country: " << getCountry() << endl;
    cout << "Continent : " << getContinent() << endl;
    cout << "Number of armies in this territory: " << getNumOfArmies() << endl;
}
