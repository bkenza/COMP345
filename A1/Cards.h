#include "Map.h"
#include <vector>
#include <string>

using namespace std;

#ifndef CARDS_H
#define CARDS_H

class Deck;
class Hand;
class Map;


class Cards
{
public:
    Cards();  // default constructor
    Cards(string type);
    ~Cards(); // destructor
//    void play(Map *map, Hand *currentHand, Deck *deck, Player *player);
    void setCardType(string type);
    string getCardType();

    Cards(const Cards &orig); // copy constructor
private:
    string *cardType;
};

#endif

#ifndef DECK_H
#define DECK_H

class Deck
{
public:
    Deck();                       // default constructor
    ~Deck();                      // destructor
    void draw(Hand *currentHand); // method that allows a player to draw a card at random from the cards remaining in the deck and place it in their hand.
    Deck(const Deck &orig);       // copy constructor
    vector<Cards *> DeckCards;
    void initializeDeck();
    void shuffleDeck();

private:
    // no private attributes for now
};

#endif

#ifndef HAND_H
#define HAND_H

class Hand
{
public:
    Hand();
    ~Hand();
    Hand(const Hand &orig);
    vector<Cards *> HandCards;
    void setPlayerID(int playerId);
    int getPlayerID();
//    vector<Cards *> DeckCards;
private:
    int playerID;
};
#endif

