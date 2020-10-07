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
    MapLoader *mapLoader = new MapLoader();
    Map *map = mapLoader->MapReader("../Maps/caribbean.map");
    return 0;
}