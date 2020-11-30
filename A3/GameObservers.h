//#include "Player.h"
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
    Observer(); // default constructor 
    Observer(const Observer &obj); // copy constructor 
    Observer &operator=(const Observer &obj); // assignment operator
    ~Observer(); // destructor 
    virtual void Update() = 0;  // virtual update method
};

#endif

#ifndef SUBJECT_H
#define SUBJECT_H

class Subject
{
public:
    Subject(); // default constructor
    ~Subject(); // destructor
    Subject(const Subject &obj); // copy constructor
    Subject &operator=(const Subject &obj); // assignment oprator 
    virtual void TurnOn(Observer *gameObserver); // method that turns on game observer
    virtual void TurnOff(Observer *gameObserver); // method that turns off game observer
    virtual void Notify(); // method that notifies observers of updates
    
private:
    vector<Observer *> observerList; // vector that contains the current observers
};

#endif

#ifndef GAMEPHASEOBSERVER_H
#define GAMEPHASEOBSERVER_H

class GamePhaseObserver : public Observer
{
public:
    GamePhaseObserver(); //default constructor 
    GamePhaseObserver(Player *player); // parametrized constructor
    GamePhaseObserver(const GamePhaseObserver &obj); // copy constructor
    GamePhaseObserver &operator=(const GamePhaseObserver &obj); // assignment operator 
    ~GamePhaseObserver(); // destructor
    void Update(); // method that prints out phase updates

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
    GameStatisticsObserver(); // default constructor 
    GameStatisticsObserver(GameEngine *gameEngine); // parametrized constructor 
    GameStatisticsObserver(const GameStatisticsObserver &obj); // copy constructor 
    GameStatisticsObserver &operator=(const GameStatisticsObserver &obj); // assignment operator 
    ~GameStatisticsObserver(); // destructor
    void Update();             // method that prints out game stats updates

private:
    GameEngine *gameEngine;
};

#endif
