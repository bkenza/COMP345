#include "Map.h"
#include <vector>
#include <string>

#ifndef CARDS_H
#define CARDS_H

using namespace std;

class Deck;
class Hand;

class Cards
{
public:
    Cards();  // default constructor
    ~Cards(); // destructor
    void play(Hand *currentHand);
    void setCardType(string type);
    string getCardType();
    Cards(const Cards &orig); // copy contructor
private:
    string *cardType;
};

#endif

#ifndef DECK_H
#define DECK_H

class Deck
{
public:
    Deck();                       // default contructor
    ~Deck();                      // destructor
    void draw(Hand *currentHand); // method that allows a player to draw a card at random from the cards remaining in the deck and place it in their hand.
    Deck(const Deck &orig);       // copy constructor
    vector<Cards *> DeckCards;
    void initiliazeDeck();
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

private:
    // no private attributes
};

#endif