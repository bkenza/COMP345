#pragma once
#include "Player.h"

class Player;
class Map;
class Deck;

class GameEngine : public Subject
{
public:
    GameEngine();                                  // Default constructor
    GameEngine(const GameEngine &obj);             // Copy constructor
    ~GameEngine();                                 // Destructor
    void startGame();                              // Method that starts the game
    void getMaps();                                // method that returns a list of maps
    int getNumPlayers();                           // Method that returns the number of players
    void setNumPlayers(int nbOfPlayers);           // Method that sets the number of players
    bool getPhaseObserverOn();                     // Method that gets observer status
    void setPhaseObserverOn(bool phaseObserverOn); // Method that sets the phase observer on
    bool getStatsObserverOn();                     // Method that gets observer status
    void setStatsObserverOn(bool statsObserverOn); // Method that sets the phase observer on
    string mapSelector(int mapNumber);             // Method that selects maps
    void startupPhase(Map *map);                   // Method for the startup phase
    void setRandomPlayerOrder();                   // Method that sets the player order randomly
    void assignTerritories(Map *map);              // Method that assigns territories to players
    void setMap(Map *map);                         // Setter for the map
    Map *getMap();                                 // getter for the map
    vector<Player *> getPlayers();                 // Method that returns a vector of current players
    void setPlayers(vector<Player *> p);           // method that sets the current players
    void mainGameLoop();
    void reinforcementPhase();
    void issueOrdersPhase();
    void executeOrdersPhase();
    void setRound(bool round);
    Player *getPlayerByID(int id);
    bool getRound();
    Deck *getDeck();

private:
    int numPlayers;
    bool phaseObserverOn;
    bool statsObserverOn;
    vector<string> mapList = {"caribbean",
                              "LOTR2",
                              "solar",
                              "sudamerica",
                              "Earth Alternate",
                              "Montreal"};
    vector<Player *> players;
    Deck *deck;
    vector<int> playerOrder;
    Map *map;
    bool firstRound;
};
