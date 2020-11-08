#ifndef MAPLOADER_H	
#define MAPLOADER_H	

#include "Map.h"	

std::vector<string> splitString(string line);	

class MapLoader	
{	
public:	
    MapLoader();                          // default constructor	
    MapLoader(const MapLoader &orig);     // copy constructor	
    ~MapLoader();                         // destructor	
    Map *MapReader(std::string filename); // Function that creates a map object	

private:	
    // no private attributes for now	
};	

#endif 	
