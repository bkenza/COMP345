#include "Territory.h"
#include <iostream>
#include <typeinfo>

using namespace TerritoryNamespace;

//default constructor
Territory::Territory() {}

//setting our Territory object with a country, continent and armies value
Territory::Territory(int id, string country, string continent, int num)
{
    this->pID = id;
    this->pCountry = &country;
    this->pContinent = &continent;
    this->pNumOfArmies = num;
}

Territory::Territory(const Territory &obj)
{
    *pCountry = *obj.pCountry;
    *pContinent = *obj.pContinent;
    //*pNumOfArmies = *obj.pNumOfArmies;
} 

//Destructor to call finalize() and free unwanted resources
Territory::~Territory() = default;

//Setter for pID datamember
void Territory::setID(int id)
{
    this->pID = id;
}

int Territory::getID()
{
    return pID;
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
     this->pNumOfArmies = num;
}

//Getter for pNumOfArmy data member
int Territory::getNumOfArmies()
{
    return pNumOfArmies;
}

//Display territory information
void Territory::displayTerritory()
{
    //cout << "Displaying information for Territory " << get << endl;
    cout << "ID: " << getID() << endl;
    cout << "Country: " << getCountry() << endl;
    cout << "Continent : " << getContinent() << endl;
    cout << "Number of armies in this territory: " << getNumOfArmies() << endl;
    
}

