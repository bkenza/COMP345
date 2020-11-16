#pragma once
#include "Player.h"

class Player;

class GameEngine : public Subject
{
public:
    GameEngine();
    GameEngine(const GameEngine &obj);
    ~GameEngine();
    void startGame();
    void getMaps();
    int getNumPlayers();
    void setNumPlayers(int nbOfPlayers);
    bool getPhaseObserverOn();
    void setPhaseObserverOn(bool phaseObserverOn);
    bool getStatsObserverOn();
    void setStatsObserverOn(bool statsObserverOn);
    string mapSelector(int mapNumber);
    void startupPhase(Map *map);
    vector<int> getPlayerOrder();
    void setPlayerOrder(vector<int> pOrder);
    void setPlayerTurn(int pTurn);
    int getPlayerTurn();
    void setRandomPlayerOrder();
    void assignTerritories(Map *map);
    void setMap(Map *map);
    Map *getMap();
    vector<Player *> getPlayers();
    void setPlayers(vector<Player *> p);
    void mainGameLoop();
    void reinforcementPhase();
    void issueOrdersPhase();
    void executeOrdersPhase();

private:
    int numPlayers;
    int phaseObserverOn;
    int statsObserverOn;
    vector<string> mapList = {"caribbean", "LOTR2", "solar", "sudamerica"};
    vector<Player *> players;
    Deck *deck;
    vector<int> playerOrder;
    int playerTurn;
    Map *map;
};
