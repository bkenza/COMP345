#include "Cards.h"
#include <algorithm>
#include <random>

using namespace std;

// default constructor
Cards::Cards()
{
    cardType = new string("");
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

void Deck::initiliazeDeck()
{
    vector<string> types = {"bomb", "reinforcement", "blockade", "airlift", "diplomacy"};
    for (int j = 0; j < types.size(); j++)
    {
        Cards newCard;
        newCard.setCardType(types[j]);
        for (int i = 0; i < 3; i++)
        {
            DeckCards.push_back(&newCard);
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

// copy contructor
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