#include "Map.h"
#include "Territory.h"
#include <iostream>
#include <vector>

using namespace TerritoryNamespace;
using namespace MapNamespace;
using namespace std; 

Map::Map() {}

Map::Map(int V) 
{
    this->V = V;

    // Create an array of sets representing adjacency lists. Size of the array will be V 
    this->adjList = new set<Territory, territory_comparator>[V];
}

//Destructor to call finalize() and free unwanted resources
Map::~Map() = default;

void Map::setVertices(int v)
{
    this->V = v;
}

int Map::getVertices()
{
    return V;
}

void Map::addEdge(Territory src, Territory dest)
{
    // Add an edge from src to dest. A new element is inserted to the adjacent list of src. 
    this->adjList[src.getID()].insert(dest.getID()); 
  
    // Since graph is undirected, add an edge from dest to src also 
    this->adjList[dest.getID()].insert(src.getID()); 
}

// Utility function to print the adjacency list representation of the map 
void Map::printMap() 
{
    for (int i = 0; i < this->getVertices(); ++i) 
    { 
        set<int, greater<int> > lst = this->adjList[i]; 
        cout << endl << "Adjacency list of vertex "
             << i << endl; 
  
        for (auto itr = lst.begin(); itr != lst.end(); ++itr) 
            cout << *itr << " "; 
        cout << endl; 
    } 
} 


struct territory_comparator
{
    bool operator() (Territory& t1, Territory& t2)
    {
        return t1.getID() < t2.getID();
    }
};
