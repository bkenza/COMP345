#pragma once
#include <vector>
#include "Territory.h"
#include <list>
#include <set>
using namespace TerritoryNamespace;

namespace MapNamespace
{
    class Map 
    {
        private:
            int V;
            set<Territory, territory_comparator>* adjList;

        public:
            Map();
            Map(int V);
            ~Map();
            void setVertices(int v);
            int getVertices();
            void addEdge(Territory src, Territory dest);
            void printMap();
            bool validate();

            struct territory_comparator
            {
                bool operator() (Territory& t1, Territory& t2);
            };
    };
}



