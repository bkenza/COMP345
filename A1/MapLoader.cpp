#include "MapLoader.h"
#include "Map.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <regex>
using namespace std;
using std::cin;
using std::cout;
using std::istringstream;
using std::string;

// Method that splits long strings into 2 strings
std::vector<string> splitString(string line)
{
    std::vector<string> words;
    istringstream ss(line);
    while (ss)
    {
        // Read a word
        string word;
        ss >> word;
        words.push_back(word);
    }
    return words;
};
MapLoader::MapLoader()
{
    // default contructor
}
MapLoader::MapLoader(const MapLoader &orig)
{
    //Copy Constructor
}
MapLoader::~MapLoader()
{
    //Destructor
}
Map *MapLoader::MapReader(string fileName)
{
    istringstream stringStream;
    ifstream inputFile(fileName);
    bool mapIsValid = true;
    std::vector<string> words;
    string line;
    string tempName; // temporary string containing the name of an entity
    bool hasContinents = false;
    bool hasCountries = false;
    bool hasBorders = false;
    int cont_counter = 0;
    int ter_counter = 0;
    //  Create map object
    Map *map = new Map();
    // For each line of the file, we want to check for a ["Map"] section, a ["Continents"] section
    for (; getline(inputFile, line);)
    {
        if (!mapIsValid)
        {
            std::cerr << "The map provided is invalid, please try again";
            map->~Map(); //destroying map
            // TODO: HOW TO IMPLEMENT THE DELETION OF THE MAP OBJECT IF IT HAPPENS TO BE INVALID? + destructor of mapreader
        }
        // if wantedString exists in the line we are currently on,
        if (line.substr(0, 3) == "map")
        {
            map->setName(line.substr(4, line.length() - 4));
            continue;
        }
        else if (!line.compare("[continents]\r"))
        { // TODO: if it doesnt work maybe add brackets []
            hasContinents = true;
            continue;
        }
        else if (!line.compare("[countries]\r"))
        {
            hasContinents = false; // set to false to that the program can go into the next if
            hasCountries = true;
            continue;
        }
        else if (!line.compare("[borders]\r"))
        {
            hasCountries = false;
            hasBorders = true;
            continue;
        }
        else if (hasContinents)
        {
            if (line.length() > 0 && line != "\r")
            {
                Continent *continent = new Continent();
                //                for(auto w : *splitString(line)){
                //                    words.push_back(w);
                //                };
                words = splitString(line);
                continent->setContinentID(++cont_counter);
                continent->setContinentName(words[0]);
                map->Continents.push_back(continent);
            }
            else
            {
                hasContinents = false;
            }
        }
        else if (hasCountries)
        {
            if (line.length() > 0 && line != "\r")
            {
                Territory *territory = new Territory();
                words = splitString(line);
                territory->setTerritoryID(++ter_counter);
                territory->setTerritoryName(words[1]);
                int index;
                std::istringstream(words[2]) >> index;
                territory->setContinentName(map->Continents[index - 1]->getContinentName());
                map->Territories.push_back(territory);
                map->Continents[index - 1]->territories.push_back(territory);
            }
            else
            {
                if (cont_counter > ter_counter)
                {
                    mapIsValid = false;
                    std::cerr << "The number of continents is greater than the number of countries. Thus, the map is invalid." << endl;
                }
                hasCountries = false;
            }
        }
        else if (hasBorders)
        {
            if (line.length() > 0 && line != "\r")
            {
                std::vector<int *> adjTerritories;
                words = splitString(line);
                int territoryId;
                std::istringstream(words[0]) >> territoryId;
                for (int i = 0; i < words.size(); i++)
                {
                    if (i != 0)
                    {
                        int adjTerritoryId;
                        std::istringstream(words[i]) >> adjTerritoryId;
                        std::vector<int*> terr_adj = map->getTerritoryById(territoryId).adjTerritories;
                        terr_adj.push_back(&adjTerritoryId);
                    }
                }
            }
            else
            {
                hasBorders = false;
            }
        }
    };
    return map;
}