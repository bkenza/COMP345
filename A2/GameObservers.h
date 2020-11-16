#include "Player.h"
#include <iostream>
#include <list>
#include <string>
#include <vector>

using namespace std;

class GameEngine;
class Player;

class Subject;
class GamePhaseObserver;
class GameStatisticsObserver;

#ifndef OBSERVER_H
#define OBSERVER_H

class Observer
{
public:
    Observer();
    Observer(const Observer &obj);
    //Observer &operator=(const Observer &obj);
    ~Observer();
    virtual void Update() = 0;
};

#endif

#ifndef SUBJECT_H
#define SUBJECT_H

class Subject
{
public:
    Subject();
    ~Subject();
    Subject(const Subject &obj);
    //Subject &operator=(const Subject &obj);
    virtual void TurnOn(Observer *gameObserver);
    virtual void TurnOff(Observer *gameObserver);
    virtual void Notify();

private:
    vector<Observer *> observerList;
};

#endif

#ifndef GAMEPHASEOBSERVER_H
#define GAMEPHASEOBSERVER_H

class GamePhaseObserver : public Observer
{
public:
    GamePhaseObserver();
    GamePhaseObserver(Player *player);
    GamePhaseObserver(const GamePhaseObserver &obj);
    GamePhaseObserver &operator=(const GamePhaseObserver &obj);
    ~GamePhaseObserver();
    void Update();

private:
    Player *player;
};

#endif

#ifndef GAMESTATISTICSOBSERVER_H
#define GAMESTATISTICSOBSERVER_H

#include "GameEngine.h"

class GameStatisticsObserver : public Observer
{
public:
    GameStatisticsObserver();
    GameStatisticsObserver(GameEngine *gameEngine);
    GameStatisticsObserver(const GameStatisticsObserver &obj);
    GameStatisticsObserver &operator=(const GameStatisticsObserver &obj);
    ~GameStatisticsObserver();
    void Update();

private:
    GameEngine *gameEngine;
};

#endif
