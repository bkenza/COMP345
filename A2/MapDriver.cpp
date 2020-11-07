#include "Map.h"
#include <iostream>

using std::cin;
using std::cout;
using std::istringstream;

int main()
{
    //==============
    //    Map
    //==============
    Map *map = new Map();

    // Set map name
    map->setName("testMap");
    Map *mapTwin = new Map(*map);

    // Get the map name
    cout << "Map name: " << map->getName() << endl;
    map->getName();

    // Get the twin map name
    cout << "Twin map name: " << mapTwin->getName() << endl;

    //=================
    //    Continent
    //=================

    // create continents
    Continent *continent1 = new Continent();
    Continent *continent2 = new Continent();
    Continent *continent3 = new Continent();
    Continent *continent4 = new Continent();

    // Set continent names and IDs
    continent1->setContinentName("Africa");
    continent1->setContinentID(1);

    continent2->setContinentName("North America");
    continent2->setContinentID(2);

    continent3->setContinentName("Asia");
    continent3->setContinentID(3);

    continent4->setContinentName("Europe");
    continent4->setContinentID(4);

    // Add continents to the map
    map->Continents.push_back(continent1);
    map->Continents.push_back(continent2);
    map->Continents.push_back(continent3);
    map->Continents.push_back(continent4);

    // Get the map & continent names and IDs
    cout << "Map name: " << map->getName() << endl;
    cout << "Continent: " << continent1->getContinentName() << " with ID: " << continent1->getContinentID() << endl;
    cout << "Continent: " << continent2->getContinentName() << " with ID: " << continent2->getContinentID() << endl;
    cout << "Continent: " << continent3->getContinentName() << " with ID: " << continent3->getContinentID() << endl;
    cout << "Continent: " << continent4->getContinentName() << " with ID: " << continent4->getContinentID() << endl;

    //From the Map class, get continents by id
    cout << "Get continent 1 by id: " << map->getContinentById(1)->getContinentName() << endl;
    cout << "Get continent 2 by id: " << map->getContinentById(2)->getContinentName() << endl;
    cout << "Get continent 3 by id: " << map->getContinentById(3)->getContinentName() << endl;
    cout << "Get continent 4 by id: " << map->getContinentById(4)->getContinentName() << endl;

    //===================
    //    Territory
    //===================

    // create territories
    Territory *territory1 = new Territory();
    Territory *territory2 = new Territory();
    Territory *territory3 = new Territory();
    Territory *territory4 = new Territory();
    Territory *territory5 = new Territory();
    Territory *territory6 = new Territory();
    Territory *territory7 = new Territory();
    Territory *territory8 = new Territory();
    Territory *territory9 = new Territory();

    // Set territory names and IDs
    territory1->setTerritoryName("Morocco");
    territory1->setTerritoryID(1);

    territory2->setTerritoryName("Egypt");
    territory2->setTerritoryID(2);

    territory3->setTerritoryName("Canada");
    territory3->setTerritoryID(3);

    territory4->setTerritoryName("USA");
    territory4->setTerritoryID(4);

    territory5->setTerritoryName("Philippines");
    territory5->setTerritoryID(5);

    territory6->setTerritoryName("Bangladesh");
    territory6->setTerritoryID(6);

    territory7->setTerritoryName("Afghanistan");
    territory7->setTerritoryID(7);

    territory8->setTerritoryName("France");
    territory8->setTerritoryID(8);

    territory9->setTerritoryName("Italy");
    territory9->setTerritoryID(9);

    //Add territories to map
    map->Territories.push_back(territory1);
    map->Territories.push_back(territory2);
    map->Territories.push_back(territory3);
    map->Territories.push_back(territory4);
    map->Territories.push_back(territory5);
    map->Territories.push_back(territory6);
    map->Territories.push_back(territory7);
    map->Territories.push_back(territory8);
    map->Territories.push_back(territory9);

    // Assign a continent to a territory
    territory1->setContinentId(1);
    map->getContinentById(1)->territories.push_back(territory1);

    territory2->setContinentId(1);
    map->getContinentById(1)->territories.push_back(territory2);

    territory3->setContinentId(2);
    map->getContinentById(2)->territories.push_back(territory3);

    territory4->setContinentId(2);
    map->getContinentById(2)->territories.push_back(territory4);

    territory5->setContinentId(3);
    map->getContinentById(3)->territories.push_back(territory5);

    territory6->setContinentId(3);
    map->getContinentById(3)->territories.push_back(territory6);

    territory7->setContinentId(3);
    map->getContinentById(3)->territories.push_back(territory7);

    territory8->setContinentId(4);
    map->getContinentById(4)->territories.push_back(territory8);

    territory9->setContinentId(4);
    map->getContinentById(4)->territories.push_back(territory9);

    // Assign players to territories
    territory1->setTerritoryPlayerID(1);
    territory2->setTerritoryID(2);

    // Create adjacency list
    territory1->adjTerritories.push_back(territory2->getTerritoryID());
    territory1->adjTerritories.push_back(territory7->getTerritoryID());

    territory2->adjTerritories.push_back(territory1->getTerritoryID());
    territory2->adjTerritories.push_back(territory7->getTerritoryID());
    territory2->adjTerritories.push_back(territory3->getTerritoryID());

    territory3->adjTerritories.push_back(territory2->getTerritoryID());
    territory3->adjTerritories.push_back(territory4->getTerritoryID());
    territory3->adjTerritories.push_back(territory8->getTerritoryID());

    territory4->adjTerritories.push_back(territory3->getTerritoryID());

    territory5->adjTerritories.push_back(territory6->getTerritoryID());
    territory5->adjTerritories.push_back(territory8->getTerritoryID());
    territory5->adjTerritories.push_back(territory9->getTerritoryID());

    territory6->adjTerritories.push_back(territory5->getTerritoryID());
    territory6->adjTerritories.push_back(territory7->getTerritoryID());

    territory7->adjTerritories.push_back(territory1->getTerritoryID());
    territory7->adjTerritories.push_back(territory2->getTerritoryID());
    territory7->adjTerritories.push_back(territory6->getTerritoryID());

    territory8->adjTerritories.push_back(territory3->getTerritoryID());
    territory8->adjTerritories.push_back(territory5->getTerritoryID());
    territory8->adjTerritories.push_back(territory9->getTerritoryID());

    territory9->adjTerritories.push_back(territory5->getTerritoryID());
    territory9->adjTerritories.push_back(territory8->getTerritoryID());

     // Validate map
    map->validate();

    // Test an invalid map: map has a continent but no territories
    Map *map2 = new Map();
    map2->setName("invalid");
    Continent *continentInvalid = new Continent();
    continentInvalid->setContinentName("Solo");
    map2->Continents.push_back(continentInvalid);

    // validate map2
    map2->validate();

    // Test another invalid map: territories are not connected
    Map *map3 = new Map();
    Continent *invalidContinent2 = new Continent();
    invalidContinent2->setContinentName("Solo2");
    map3->Continents.push_back(invalidContinent2);

    Territory *invalidTerritory = new Territory();
    invalidTerritory->setTerritoryID(5);
    invalidContinent2->territories.push_back(invalidTerritory);
    map3->Territories.push_back(invalidTerritory);

    Territory *invalidTerritory2 = new Territory();
    invalidTerritory2->setTerritoryID(6);
    invalidContinent2->territories.push_back(invalidTerritory2);
    map3->Territories.push_back(invalidTerritory2);

    // validate map3
    map3->validate();
}
