#ifndef TERRITORY_H
#define TERRITORY_H

#include <string>
using namespace std;

namespace TerritoryNamespace
{
    class Territory
    {
    private:
        int territoryID;
        int playerID; // only one player can own a territory
        string *pCountry;
        string *pContinent;
        int playerNumOfArmies;

    public:
        Territory(); // constructor
        Territory(int territoryId, int playerId, string country, string continent, int num);
        Territory(const Territory &obj);
        ~Territory();
        void setTerritoryID(int territoryId);
        void setTerritoryPlayerID(int playerId);
        void setCountry(string country);
        void setContinent(string continent);
        void setNumOfArmies(int num);
        int getTerritoryID();
        int getTerritoryPlayerID();
        string getCountry();
        string getContinent();
        int getNumOfArmies();
        void displayTerritory();
    };
} // namespace TerritoryNamespace

#endif