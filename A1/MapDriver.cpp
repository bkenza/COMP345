//Purpose of this file is to create different map objects and checks whether they are valid or not
#include <iostream>
#include "Territory.h"
#include "Map.h"

using namespace TerritoryNamespace;
using namespace MapNamespace;
using namespace std;

int main()
{
    //Territory t1;
    //Territory t2;
    Territory t1(1, "Canada", "North America", 4);
    Territory t2(2, "China", "Asia", 2);
    Territory t3(3, "Australia", "Asia", 3);

    /*t1.setID(1);
    t1.setContinent("Unknown");
    t1.setCountry("Fack");
    t1.setNumOfArmies(10);

    t2.setID(2);
    t2.setContinent("Asia");
    t2.setCountry("Malaysia");
    t2.setNu*/

    Map m1(6);
    //Map subMap1;
    //Map subMap2;

    t1.displayTerritory();
    t2.displayTerritory();
    /*cout << "Country: " << t1.getID() << endl;
    cout << "Country: " << t1.getCountry() << endl;
    cout << "Continent : " << t1.getContinent() << endl;
    cout << "Number of armies in this territory: " << t1.getNumOfArmies() << endl;*/
    /*m1.addEdge(0, 1);
    m1.addEdge(0, 4);
    m1.addEdge(1, 2);
    m1.addEdge(1, 3);
    m1.addEdge(1, 4);
    m1.addEdge(2, 3);
    m1.addEdge(3, 4);
    m1.printMap();*/

    return 0;
}

