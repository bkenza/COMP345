#include "Map.h"
#include <iostream>
#include <cstdlib>

using namespace std;

// Default constructor
Map::Map()
{
    name = new string("");
}

// Copy constructor
Map::Map(const Map &orig)
{
    name = new string(*orig.name);
}

// Create a map
Map::Map *createMap(int V)
{
    Map *map = new Map;
    map->V = V;
    //create an array of adjacency list. size of array - V
    map->arr = new Map::MapAdjList[V];
    //initialize with NULL (e.g root=NULL)
    for (int i = 0; i < V; i++)
    {
        map->arr[i].head = NULL;
    }
    return map;
}

// Set map name
void Map::setName(std::string title)
{
    *name = title;
}

// Get map name
std::string Map::getName()
{
    return *name;
}

//TODO: not sure if this code is correct
// Create a new node
Map::MapAdjListNode *newNode(int id)
{
    Map::MapAdjListNode *nptr = new Map::MapAdjListNode;
    nptr->id = id;
    nptr->next = NULL;
    return nptr;
}

//add an edge to an undirected map
void addEdge(Map *map, int territory1, int territory2)
{
    //Add an edge from territory1 to territory2. A new node added to the adjacency list of src
    //node added at beginning
    Map::MapAdjListNode *nptr = newNode(territory2);
    nptr->next = map->arr[territory1].head;
    map->arr[territory1].head = nptr;
    //connect from territory2 to src (since undirected)
    nptr = newNode(territory1);
    nptr->next = map->arr[territory2].head;
    map->arr[territory2].head = nptr;
}

//function to print the map
void printMap(Map *map)
{
    //loop over each adjacent list
    for (int i = 0; i < map->V; i++)
    {
        Map::MapAdjListNode *root = map->arr[i].head;
        cout << "Adjacency list of vertex " << i << endl;
        //loop over each node in list
        while (root != NULL)
        {
            cout << root->id << " ";
            root = root->next;
        }
        cout << endl;
    }
}

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

int Territory::getTerritoryID()
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
