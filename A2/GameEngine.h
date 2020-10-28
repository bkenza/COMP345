#include "Player.h"
#ifndef A2_GAMEENGINE_H
#define A2_GAMEENGINE_H

class GameEngine
{
public:
    GameEngine();
    GameEngine(const GameEngine &obj);
    ~GameEngine();
    void startGame();
    void getMaps();
    int getNumPlayers();
    void setNumPlayers(int nbOfPlayers);
    bool getObserversOn();
    void setObserversOn(bool observersOn);
    string mapSelector(int mapNumber);

private:
    int numPlayers;
    bool observersOn;
    string mapList[4] = {"caribbean", "LOTR2", "solar", "sudamerica"};
    vector<Player *> players;
    Deck *deck;
};

#endif //A2_GAMEENGINE_H
