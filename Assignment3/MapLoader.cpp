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

int amountOccurence(string line, char ch)
{
    int lineSize = line.length();
    int amount = 0;

    for (int i = 0; i < lineSize; i++)
    {
        if (ch == line[i])
        {
            amount++;
        }
    }

    return amount;
};

int nthOccurrence(string line, char ch, int n)
{
    int occurence = 0;
    int lineSize = line.length();

    for(int i = 0; i < lineSize; i++)
    {
        if (ch == line[i])
        {
            occurence++;
        }

        if (n == occurence)
        {
            return i;
        }
    }

    return -1;
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

ConquestFileReader::ConquestFileReader()
{

}

ConquestFileReader::~ConquestFileReader()
{

}

ConquestFileReader::ConquestFileReader(const ConquestFileReader &orig)
{

}

Map* ConquestFileReader::MapReader(std::string filename)
{
    bool mapIsValid = true;  // valid until proven otherwise
    ifstream inputFile(filename);
    string line;
    bool startSection = true; // We start at the beginning of file. Useless. For readability.
    bool contSection = false; // Are we in the continent section?
    bool terrSection = false; // Are we in the territory section?
    int contCount = 0;
    int terrCount = 0;

    Map* map = new Map();

    for (; getline(inputFile, line);)
    {
        if (line.length() == 1)
        {
            continue;
        }

        if (startSection)
        {
            // Continents line can happen at any time. Must be the first thing to be checked.
            if (!line.compare("[Continents]\r"))
            {
                startSection = false;
                contSection = true;
                continue;
            }

            // Only process when the line contains the name of the map.
            else if (line.substr(0, 5) == "image")
            {
                map->setName(line.substr(6, line.length() - 6 - 5));
                continue;
            }
        }

        // Line right after [Continents]
        else if (contSection)
        {
            // Territories line can happen at any time. Must be the first thing to be checked.
            if (!line.compare("[Territories]\r"))
            {
                contSection = false;
                terrSection = true;
                continue;
            }

            // Process every line in the continent section
            else
            {
                Continent* cont = new Continent();

                size_t delimPos = line.find('=');
                string contName = line.substr(0, delimPos);

                cont->setContinentID(++contCount);
                cont->setContinentName(contName);

                map->Continents.push_back(cont);
            }
        }

        // Line right after [Territories].
        else
        {
            Territory* terr = new Territory();

            // Start processing territory name
            size_t delimPos = line.find(',');
            string terrName = line.substr(0, delimPos);
            // End processing territory name

            // Start processing continent name
            string truncLine = line.substr(nthOccurrence(line, ',', 3) + 2); // Remove everything before continent name
            delimPos = truncLine.find(',');
            string contName = truncLine.substr(0, delimPos); // Extracts continent name
            // End processing continent name

            // Start processing continent ID
            int contID = map->getContIDByName(contName);
            // End processing continent ID

            // Start processing adjacent territories
            truncLine = truncLine.substr(truncLine.find(',') + 2); // Start of adjacent territories.
            int commaOccurenceNb = amountOccurence(truncLine, ',');

            for (int i = 1; i <= commaOccurenceNb + 1; i++)
            {
                int commaPos = truncLine.find(',');
                string currAdjTerr;

                if (commaPos == -1) // Last adjacent territory on the line
                {
                    currAdjTerr = truncLine.substr(0, truncLine.length() - 1); // Removes '\n'
                }

                else // There are >= 2 adjacent territories
                {
                    currAdjTerr = truncLine.substr(0, commaPos); // Extracts first adj terr
                    truncLine = truncLine.substr(commaPos + 2);
                }

                terr->adjTerrNames.push_back(currAdjTerr);
            }
            // End processing adjacent territories

            terr->setTerritoryID(++terrCount);
            terr->setTerritoryName(terrName);
            terr->setContinentId(contID);
            terr->setContinentName(contName);

            map->Territories.push_back(terr);
        }
    }

    // Filling adjTerritories<int> vector
    int listSize = map->Territories.size();

    for (int i = 0; i < listSize; i++)
    {
        Territory* currTerr = map->Territories[i];
        int adjListSizeStr = (currTerr->adjTerrNames).size();

        for (int j = 0; j < adjListSizeStr; j++)
        {
            currTerr->adjTerritories.push_back(map->getTerrIDByName(currTerr->adjTerrNames[j]));
        }
    }

    // TESTING //
    Territory* temp;
    Continent* temp2;
    int listSize1 = map->Territories.size();
    int listSize2 = map->Continents.size();

    for (int i = 0; i < listSize1; i++)
    {
        temp = map->Territories[i];
        /*cout << "\nTerritory Name: " << temp->getTerritoryName() << " with length " << temp->getTerritoryName().length() << endl;
        cout << "Territory ID: " << temp->getTerritoryID() << endl;
        cout << "Territory Continent Name: " << temp->getContinent() << " with length " << temp->getContinent().length() << endl;
        cout << "Territory Continent ID: " << temp->getContinentId() << endl;
        cout << "Territory has " << temp->adjTerritories.size() << " adjacent territories" << endl;*/

        int adjTerritoriesSize = temp->adjTerritories.size();
        int adjTerrNameSize = temp->adjTerrNames.size();

        for (int j = 0; j < adjTerritoriesSize; j++)
        {
            //cout << temp->adjTerritories.size() << endl;
            //cout << "Territory ID [ " << temp->adjTerritories[i] << " ] has the name : " << map->getTerritoryById(temp->adjTerritories[j]) << endl;
            //cout << temp->getTerritoryName() << " has adjacent IDs: ";
            //cout << temp->adjTerritories[j] << "," << endl;
        }

        cout << endl;
    }

    /*for (int i = 0; i < listSize2; i++)
    {
        temp2 = map->Continents[i];
        cout << "Continent Name: " << temp2->getContinentName() << " with length " << temp2->getContinentName().length() << endl;
        cout << "Continent ID: " << temp2->getContinentID() << endl << endl;
    }*/
    // END TESTING //

    return map;
}

ConquestFileReaderAdapter::ConquestFileReaderAdapter()
{

}

ConquestFileReaderAdapter::ConquestFileReaderAdapter(ConquestFileReader *newReader)
{
    reader = newReader;
}

ConquestFileReaderAdapter::~ConquestFileReaderAdapter() noexcept
{

}

ConquestFileReaderAdapter::ConquestFileReaderAdapter(const ConquestFileReader &orig)
{

}

Map* ConquestFileReaderAdapter::MapReader(std::string filename)
{
    return reader->MapReader(filename);
}

int Map::getContIDByName(string name)
{
    int listSize = Continents.size();

    for (int i = 0; i < listSize; i++)
    {
        if (name == Continents[i]->getContinentName())
        {
            return Continents[i]->getContinentID();
        }
    }

    return -99;
}
