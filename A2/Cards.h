#include <vector>
#include "Map.h"
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
    Cards(string type); // constructor
    ~Cards(); // destructor
    void setCardType(string type); // card type setter
    string getCardType(); // card type getter

    Cards(const Cards &orig); // copy constructor
private:
    string *cardType; // card type/name
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
    vector<Cards *> DeckCards; // vector of card pointers
    void initializeDeck(); // Method to initialize the deck of cards
    void shuffleDeck(); // Method to shuffle the deck of cards
private:
    // no private attributes for now
};

#endif

#ifndef HAND_H
#define HAND_H

class Hand
{
public:
    Hand(); // default constructor
    ~Hand(); // destructor
    Hand(const Hand &orig); //copy constructor
    vector<Cards *> HandCards; // vector of card pointers
    void setPlayerID(int playerId); // method to set the playerID
    int getPlayerID(); // method to get the playerID
private:
    int playerID; // ID of a given player
};
#endif

