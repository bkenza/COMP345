#ifndef MAPLOADER_H	
#define MAPLOADER_H	

#include "Map.h"	

std::vector<string> splitString(string line);
int nthOccurrence(string line, char ch, int n);
int amountOccurence(string line, char ch);

class MapLoader
{	
public:	
    MapLoader();                          // default constructor	
    MapLoader(const MapLoader &orig);     // copy constructor	
    virtual ~MapLoader();                         // destructor
    virtual Map *MapReader(std::string filename); // Function that creates a map object

private:	
    // no private attributes for now	
};

class ConquestFileReader
{
public:
    ConquestFileReader();
    ConquestFileReader(const ConquestFileReader& orig);
    ~ConquestFileReader();
    Map* MapReader(std::string filename);
};

class ConquestFileReaderAdapter : public MapLoader
{
private:
    ConquestFileReader* reader;

public:
    ConquestFileReaderAdapter();
    ~ConquestFileReaderAdapter() override;
    ConquestFileReaderAdapter(const ConquestFileReader& orig);
    ConquestFileReaderAdapter(ConquestFileReader* reader);
    Map* MapReader(std::string filename) override;
};

#endif 	
