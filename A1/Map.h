#ifndef MAP_H
#define MAP_H

#include <iostream>
#include <cstdlib>
using namespace std;
#include <vector>

class Map
{
private:
    std::string *name; //name/title of a given map
public:
    struct MapAdjListNode
    {
        int id;
        MapAdjListNode *next;
    };
    MapAdjListNode mapAdjListNode;

    struct MapAdjList
    {
        MapAdjListNode *head; //pointer to head node of list
    };
    MapAdjList mapAdjList;

    Map();                // default constructor
    Map(const Map &orig); // Copy constructor
    ~Map();               // destructor
    int V;
    Map::MapAdjList *arr;
    bool validate();
    Map *createMap(int V);
    MapAdjListNode *newNode(int);    // method to create a new node
    void addEdge(Map *, int, int);   // method to add an edge between two territories
    void printMap(Map *);            // method to print the map (all territories and their adjacent territories)
    void setName(std::string title); // set the name of a given map
    std::string getName();           // get the name of a given map
};

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

#endif