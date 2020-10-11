#include "MapLoader.h"
#include <iostream>
#include <cstdlib>
#include <sstream>
#include <fstream>
#include <regex>
#include <stdio.h>

using std::cin;
using std::cout;
using std::istringstream;

int main()
{
    // Create a Map & MapLoader objects
    MapLoader *mapLoader = new MapLoader();
    Map *map = mapLoader->MapReader("../Maps/caribbean.map");

    // Check if the map is valid:
    // 1. Check that continents are connected
    // 2. Check that subgraphs (territories) are connected
    // 3. Check that each territory is found in only one continent
    map->validate();

    // Print a list of Continents and Territories inside the map
    cout << "List of Continents and their Territories"
         << endl;
    cout << "----------------------------------------\n"
         << endl;
    for (auto c : map->Continents)
    {
        cout << c->getContinentName() << endl;
        cout << "----------------\n"
             << endl;
        for (auto t : c->territories)
        {
            cout << "  " + t->getTerritoryName() << endl;
        }
        cout << "\n"
             << endl;
    }

    return 0;
}