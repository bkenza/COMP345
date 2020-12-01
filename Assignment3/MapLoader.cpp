#include "MapLoader.h"
//#include "Map.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <regex>

using namespace std;
using std::cin;
using std::cout;
using std::istringstream;
using std::string;

/**
 * Method that splits a long string (sentence) into multiple strings
 * @param line
 * @return words<string>
 */
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

/**
 * Default constructor
 */
MapLoader::MapLoader()
{
}

/**
 * copy constructor
 */
MapLoader::MapLoader(const MapLoader &orig)
{
}

/**
 * Destructor
 */
MapLoader::~MapLoader()
{
}

/**
 * Method that loads a map file and creates a map object in order to populate it as a connected graph
 * First
 * @param fileName
 * @return map
 */
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
        }
        // if wantedString exists in the line we are currently on,
        if (line.substr(0, 3) == "map")
        {
            map->setName(line.substr(4, line.length() - 4));
            continue;
        }
        else if (!line.compare("[continents]\r"))
        {
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
                territory->setContinentId(index);
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
                words = splitString(line);
                int territoryId;
                std::istringstream(words[0]) >> territoryId;
                for (int i = 1; i < words.size() - 1; i++)
                {
                    int adjTerritoryId;
                    std::istringstream(words[i]) >> adjTerritoryId;
                    map->Territories[territoryId - 1]->adjTerritories.push_back(adjTerritoryId);
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