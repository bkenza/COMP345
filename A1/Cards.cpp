#include "Cards.h"

using namespace std;

// default contructor
Cards::Cards(){
    cardType = new string("");
    id = new int(1);
}

// copy contructor
Cards::Cards(const Cards& orig) {
    cardType = new string(*orig.cardType);
    id = new int(*orig.id);
}

void setCardType(string type) {
    *cardType = type;
}

string getCardType() {
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
Deck::Deck() {

}
