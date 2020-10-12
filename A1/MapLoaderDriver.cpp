#include "MapLoader.h"
#include <iostream>
#include <regex>

using std::cin;
using std::cout;
using std::istringstream;

int mlmain()
{
    // Create a Map & MapLoader objects
    MapLoader *mapLoader = new MapLoader();
    Map *map = mapLoader->MapReader("../Maps/caribbean.map");

    // Check if the map is valid:
    // 1. Check that continents are connected
    // 2. Check that sub-graphs (territories) are connected
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