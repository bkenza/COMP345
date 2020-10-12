#include "Cards.h"
#include <iostream>


using std::cin;
using std::cout;

int cmain() {

    Deck *deck = new Deck();
    deck->initializeDeck(); // creates a deck of cards of all different kinds

    Hand *hand = new Hand(); // creates a hand object

    // Draw cards from the deck to fill hand
    deck->draw(hand);
    deck->draw(hand);
    deck->draw(hand);
    deck->draw(hand);
    deck->draw(hand);

    cout << "Cards added to hand are:" <<endl;

    for (int i=0; i < hand->HandCards.size(); i++) {
        cout << hand->HandCards[i]->getCardType() <<endl;
    }

    return 0;
}