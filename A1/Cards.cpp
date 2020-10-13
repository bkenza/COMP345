#include "Cards.h"
#include <algorithm>
#include <random>

using namespace std;

/**
 * Default constructor
 */
Cards::Cards()
{
    cardType = new string("");
}

/**
 * Constructor with a string parameter
 * @param type
 */
Cards::Cards(string type) {
    *cardType = type;
}

/**
 * Copy constructor
 * @param orig
 */
Cards::Cards(const Cards &orig)
{
    cardType = new string(*orig.cardType);
}
/**
 * Method that sets the card type/name
 * @param type
 */
void Cards::setCardType(string type)
{
    *cardType = type;
}

/**
 * Method that gets the card type/name
 * @return
 */
string Cards::getCardType()
{
    return *cardType;
}

/**
 * Destructor
 */
Cards::~Cards()
{
    delete cardType;
}

//---------------------------
//     Deck
//---------------------------

/**
 * Default constructor
 */
Deck::Deck()
{
}

/**
 * Destructor
 */
Deck::~Deck()
{
    for (auto c : DeckCards)
    {
        delete c;
    }
    DeckCards.clear();
}

/**
 * Copy constructor
 * @param orig
 */
Deck::Deck(const Deck &orig)
{
    for (auto &&t : orig.DeckCards)
    {
        DeckCards.push_back(new Cards(*t));
    }
}

/**
 * Method to draw a card from the deck
 * @param currentHand
 */
void Deck::draw(Hand *currentHand)
{
    if (DeckCards.empty())
    {
        cout << "No more cards in the deck, sorry!" << endl; // output this if the deck is empty
    }
    else
    {
        currentHand->HandCards.push_back(DeckCards.back()); // add the last card in the deck to the current hand
        DeckCards.pop_back();                               // remove the drawn card from the deck
    }
}

/**
 * Method to initialize & shuffle the deck of cards
 */
void Deck::initializeDeck()
{
    vector<string> types = {"bomb", "reinforcement", "blockade", "airlift", "diplomacy"};
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

/**
 * Method that shuffles the deck of cards
 */
void Deck::shuffleDeck()
{
    mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());
    shuffle(std::begin(DeckCards), std::end(DeckCards), rng);
};

//------------------------------
//         Hand
//------------------------------

/**
 * Default constructor
 */
Hand::Hand(){
};

/**
 * Copy constructor
 * @param orig
 */
Hand::Hand(const Hand &orig)
{
    for (auto &&t : orig.HandCards)
    {
        HandCards.push_back(new Cards(*t));
    }
};

/**
 * Destructor
 */
Hand::~Hand()
{
    for (auto c : HandCards)
    {
        delete c;
    }
    HandCards.clear();
}

/**
 * Method that sets the playerID
 * @param playerId
 */
void Hand::setPlayerID(int playerId) {
    playerID = playerId;
}

/**
 * Method that gets the playerID
 * @return
 */
int Hand::getPlayerID() {
    return playerID;
}