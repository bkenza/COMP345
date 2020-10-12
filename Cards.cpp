
#include "Cards.h"
#include <algorithm>
#include <random>

using namespace std;

// default constructor
Cards::Cards()
{
    cardType = new string("");
}

Cards::Cards(string type) {
    *cardType = type;
}

// copy constructor
Cards::Cards(const Cards &orig)
{
    cardType = new string(*orig.cardType);
}

void Cards::setCardType(string type)
{
    *cardType = type;
}

// Card type getter
string Cards::getCardType()
{
    return *cardType;
}

//Destructor
Cards::~Cards()
{
    delete cardType;
}

// which creates an order and adds it to the player’s list of orders and then returns the card to the deck
//void Cards::play(Map *map, Hand *currentHand, Deck *deck, Player *player) {
////    int playerID = currentHand->getPlayerID();
////    Player *currentPlayer = map->getPlayerById(playerID);
//
//
//    // create an order & add it to player's order list
//
//    player->issueOrder(*cardType);
//
//    int removalCounter = 0;
//    Cards current;
//
//    // Remove card from current hand
//    for (int p =0; p < currentHand->HandCards.size(); p++) {
//        if (currentHand->HandCards[p]->getCardType() == cardType && removalCounter == 0) {
//            current = *currentHand->HandCards[p];
//            currentHand->HandCards.erase(currentHand->HandCards.begin() + p);
//
//            removalCounter++;
//        }
//    }
//
//    // Return current card to the deck & shuffle it
//    deck->DeckCards.push_back(&current);
//    deck->shuffleDeck();
//}

//---------------------------
//     Deck
//---------------------------
Deck::Deck()
{
}

// Destructor
Deck::~Deck()
{
    for (auto c : DeckCards)
    {
        delete c;
    }
    DeckCards.clear();
}

// copy constructor
Deck::Deck(const Deck &orig)
{
    for (auto &&t : orig.DeckCards)
    {
        DeckCards.push_back(new Cards(*t));
    }
}

// Method to draw a card from the deck
void Deck::draw(Hand *currentHand)
{
    if (DeckCards.empty())
    {
        cout << "No more cards in the deck, sorry!" << endl;
    }
    else
    {
        currentHand->HandCards.push_back(DeckCards.back()); // add the last card in the deck to the current hand
        DeckCards.pop_back();                               // remove the drawn card from the deck
    }
}

void Deck::initializeDeck()
{
    vector<string> types = {"bomb", "reinforcement", "blockade", "airlift", "diplomacy"};
//    vector<Cards *> cardTypes = {new Cards("bomb"), new Cards("reinforcement"), new Cards("blockade"), new Cards("airlift"), new Cards("diplomacy")};
    for (int j = 0; j < types.size(); j++)
    {
        Cards *card = new Cards();
        card->setCardType(types[j]);
        for (int i = 0; i < 6; i++)
        {
            DeckCards.push_back(card);
        }
    }
    shuffleDeck();
}

// Method that shuffles a given deck of cards
void Deck::shuffleDeck()
{
    auto rng = default_random_engine{};
    shuffle(begin(DeckCards), end(DeckCards), rng);
};

//------------------------------
//         Hand
//------------------------------

// default constructor
Hand::Hand(){
    // empty hehe
};

// copy constructor
Hand::Hand(const Hand &orig)
{
    for (auto &&t : orig.HandCards)
    {
        HandCards.push_back(new Cards(*t));
    }
};

Hand::~Hand()
{
    for (auto c : HandCards)
    {
        delete c;
    }
    HandCards.clear();
}

void Hand::setPlayerID(int playerId) {
    playerID = playerId;
}

int Hand::getPlayerID() {
    return playerID;
}