#ifndef MAP_H
#define MAP_H

#include <iostream>
#include <cstdlib>
using namespace std;
#include <vector>
// #include "Territory.h"

namespace MapNamespace
{
    class Map
    {
    private:
        // no private attributes for now
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

        Map(); //constructor
        // Map(int V); // Create a map of size V
        ~Map(); // destructor
        // TODO: do we need a copy constructor
        int V;
        Map::MapAdjList *arr;
        bool validate();
        Map *createMap(int V);
        MapAdjListNode *newNode(int);  // method to create a new node
        void addEdge(Map *, int, int); // method to add an edge between two territories
        void printMap(Map *);          // method to print the map (all territories and their adjacent territories)
    };
} // namespace MapNamespace

#endif