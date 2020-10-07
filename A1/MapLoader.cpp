#include "MapLoader.h"
#include "Map.h"

#include <iostream>
#include <sstream>
#include <fstream>
#include <regex>
#include <stdio.h>

using namespace std;
using std::cin;
using std::cout;
using std::istringstream;
using std::string;

// Method that splits long strings into 2 strings
string *splitString(string line)
{
    static string words[2];
    istringstream ss(line);
    for (int i = 0; i < 2; i++)
    {
        // Read a word
        string word;
        ss >> word;
        words[i] = word;
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
    string *words;
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
            map->setName(line.substr(5, line.length() - 1));
            continue;
        }
        else if (!line.compare("[Continents]"))
        { // TODO: if it doesnt work maybe add brackets []

            hasContinents = true;
            continue;
        }
        else if (!line.compare("[Countries"))
        {

            hasCountries = true;
            continue;
        }
        else if (!line.compare("[borders"))
        {
            hasBorders = true;
            continue;
        }
        else if (hasContinents)
        {
            if (line.length() > 0)
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
            if (line.length() > 0)
            {
                Territory *territory = new Territory();
                words = splitString(line);
                territory->setTerritoryID(++ter_counter);
                territory->setTerritoryName(words[0]);
                map->Territories.push_back(territory);
            }
            else
            {
                if (cont_counter > ter_counter)
                {
                    std::cerr << "The number of continents is greater than the number of countries. Thus, the map is invalid." << endl;
                }
                mapIsValid = false;
                hasCountries = false;
            }
        }
        // else if (hasBorders)
        // {
        //     if (line.length() > 0)
        //     {
        //     }

        //     else
        //     {
        //         hasBorders = false;
        //     }
        // }

        // step 2: create new map object
    };
    return map;
}
