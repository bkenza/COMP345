#pragma once
#include <string>
using namespace std;

namespace TerritoryNamespace
{
    class Territory
    {
        private:
            int pID;
            string* pCountry;
            string* pContinent;
            int pNumOfArmies;

        public:
            Territory();
            Territory(int id, string country, string continent,int num);
            Territory(const Territory &obj);
            ~Territory();
            void setID(int id);
            void setCountry(string country);            
            void setContinent(string continent);
            void setNumOfArmies(int num);
            int getID();
            string getCountry();
            string getContinent();
            int getNumOfArmies();
            void displayTerritory();
    };
}

