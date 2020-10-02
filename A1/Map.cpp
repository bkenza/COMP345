#include "Map.h"
#include <iostream>
#include <cstdlib>

using namespace std;
using namespace MapNamespace;

Map::Map()
{
} //default contructor

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
