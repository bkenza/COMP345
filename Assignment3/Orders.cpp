#include <iomanip> // To format output.
#include <cstdlib>
#include "Orders.h"
#include "Map.h"
#include "Player.h"
#include "Cards.h"

using std::cout;
using std::endl;
using std::left;
using std::ostream;
using std::setfill;
using std::setw;

/**
 *  The labels of the orders, which are constant and static.
 */
const string deploy::label = "deploy";
const string AdvanceOrder::advance::label = "advance";
const string bomb::label = "bomb";
const string blockade::label = "blockade";
const string airlift::label = "airlift";
const string negotiate::label = "negotiate";

/**
 * Default constructor
 */
OrdersList::OrdersList()
{
}

/**
 * Destructor
 */
OrdersList::~OrdersList()
{
    int listSize = orders.size();

    for (int i = 0; i < listSize; i++) // Delete memory for orders, which are always dynamically allocated.
        delete orders[i];
}

/**
 * Copy constructor: makes a deep copy of a list
 * @param oldList
 */
OrdersList::OrdersList(const OrdersList &oldList)
{
    int listSize = oldList.orders.size();
    orders = vector<Order *>(listSize);

    for (int i = 0; i < listSize; i++) // Same objects, but in different memory locations.
        orders[i] = oldList.orders[i]->clone();

    cout << "The list has been copied!" << endl;
}

Order::Order()
{
    currentPlayer = nullptr;
    enabled = true;
}

Order::Order(Player &currentPlayer)
{
    this->currentPlayer = &currentPlayer;
    enabled = true;
}

/**
 * Destructor
 */
Order::~Order()
{
    currentPlayer = nullptr;
}

/**
 * Destructor
 */

deploy::deploy() : Order()
{
    target = nullptr;
    amount = nullptr;
}

deploy::deploy(Territory &target, Player &currentPlayer, int amount) : Order(currentPlayer)
{
    this->target = &target;
    int *copiedAmount = new int(amount); // Because our data member is an int pointer.
    this->amount = copiedAmount;
}

deploy::~deploy()
{
    target = nullptr;
    currentPlayer = nullptr;
    delete amount;
}

AdvanceOrder::advance::advance() : Order()
{
    source = nullptr;
    target = nullptr;
    amount = nullptr;
}

AdvanceOrder::advance::advance(Territory &source, Territory &target, Player &currentPlayer, int amount) : Order(currentPlayer)
{
    this->source = &source;
    this->target = &target;
    int *copiedAmount = new int(amount);
    this->amount = copiedAmount;
}

/**
 * Destructor
 */
AdvanceOrder::advance::~advance()
{
    source = nullptr;
    target = nullptr;
    delete amount;
}

bomb::bomb() : Order()
{
    target = nullptr;
}

bomb::bomb(Territory &target, Player &currentPlayer) : Order(currentPlayer)
{
    this->target = &target;
}

/**
 * Destructor
 */
bomb::~bomb()
{
    target = nullptr;
}

blockade::blockade() : Order()
{
    target = nullptr;
}

blockade::blockade(Territory &target, Player &currentPlayer) : Order(currentPlayer)
{
    this->target = &target;
}

/**
 * Destructor
 */
blockade::~blockade()
{
    target = nullptr;
}

airlift::airlift() : Order()
{
    source = nullptr;
    target = nullptr;
    amount = nullptr;
}

airlift::airlift(Territory &source, Territory &target, Player &currentPlayer, int amount) : Order(currentPlayer)
{
    this->source = &source;
    this->target = &target;
    int *copiedAmount = new int(amount);
    this->amount = copiedAmount;
}

/**
 * Destructor
 */
airlift::~airlift()
{
    source = nullptr;
    target = nullptr;
    delete amount;
}

/**
 * Destructor
 */
negotiate::negotiate() : Order()
{
    targetPlayer = nullptr;
}

negotiate::negotiate(Player &targetPlayer, Player &currentPlayer) : Order(currentPlayer)
{
    this->targetPlayer = &targetPlayer;
}

negotiate::~negotiate()
{
    targetPlayer = nullptr;
}

/**
 * Method that adds an order to the orders vector
 * @param o
 */
void OrdersList::addOrder(Order *o)
{
    if (o == nullptr) // See OrdersFactory.
        cout << "This is a null pointer! Adding operation failed!" << endl;
    else
    {
        orders.push_back(o);
        cout << "Order has been added to the list! Your list now looks like: \n";
        cout << *this << endl;
    }
}

/**
 * Method that deletes an order
 * @param pos
 */
void OrdersList::deleteOrder(int pos)
{
    int listSize = orders.size();

    if (listSize == 0) // Empty list so nothing to be done.
        cout << "Nothing to erase!" << endl;
    else if (pos > listSize || pos < 1) // Bounds check.
        cout << "Please select a valid position!" << endl;
    else
    {
        delete orders[pos - 1];                 // Order objects are dynamically allocated, so frees memory.
        orders.erase(orders.begin() + pos - 1); // Once memory freed, delete actual pointer from list.
        cout << "Erase at position " << pos << " successful! Your list now looks like: \n";
        cout << *this << endl;
    }
}

/**
 * Method that moves an order
 * @param pos1
 * @param pos2
 */
void OrdersList::moveOrder(int pos1, int pos2)
{
    int listSize = orders.size(); // Compute size to check if a move can be performed.

    if (listSize == 0) // Empty list so nothing to be done.
        cout << "There is nothing to move!" << endl;
    else if (listSize == 1) // Only 1 item in the list, so nothing to be done.
        cout << "You need at least two orders to perform a swap!" << endl;
    else if (pos1 > listSize || pos2 > listSize || pos1 < 1 || pos2 < 1) // Bounds check.
        cout << "One or both of your positions are invalid!" << endl;
    else
    {
        Order *temp = orders[pos1 - 1]; // Swap pointers. Address of actual object unchanged.
        orders[pos1 - 1] = orders[pos2 - 1];
        orders[pos2 - 1] = temp;
        cout << "Order " << pos1 << " and Order " << pos2 << " have been swapped! Your list now looks like: \n";
        cout << *this << endl;
    }
}

/**
 * Method that executes an order
 */
void OrdersList::executeOrders()
{
    int listSize = orders.size();

    if (listSize == 0)
        cout << "Nothing to execute!" << endl;
    else
    {
        for (int i = 0; i < listSize; i++)
        {
            orders[i]->execute();
            delete orders[i];
        }

        orders.clear();
        cout << "Orders have been executed!" << endl;
    }
}

/**
 * Assignment operator
 * @param rhsList
 * @return
 */
OrdersList &OrdersList::operator=(const OrdersList &rhsList) // Releases resources by LHS and deep-copy
{                                                            // to RHS
    if (&rhsList == this)                                    // Checks for self assignment
        return *this;

    int lhsListSize = orders.size();
    int rhsListSize = rhsList.orders.size();

    for (int i = 0; i < lhsListSize; i++)
        delete orders[i];

    orders = vector<Order *>(rhsListSize); // Reallocate memory for vector of size RHS

    for (int i = 0; i < rhsListSize; i++)
        orders[i] = rhsList.orders[i]->clone(); // Clone RHS element into LHS

    return *this;
}

int OrdersList::getOrdersListSize()
{
    return orders.size();
}

Order *OrdersList::getOrder(int index)
{
    if (index < orders.size() && index >= 0)
    {
        return orders[index];
    }
    return nullptr;
}

/**
 * Prints the list using cout.
 * @param strm
 * @param ol
 * @return
 */
ostream &operator<<(ostream &strm, const OrdersList &ol)
{
    int listSize = ol.orders.size(); // For iteration
    const int MAX_WIDTH = 9;         // To force the amount of space a string takes.
    const char separator = ' ';      // If string.length() < 9, fill with empty spaces.

    for (int i = 0; i < listSize; i++)
        strm << left << setw(MAX_WIDTH) << setfill(separator) << i + 1 << " | "; // Left formatted

    strm << "\n";

    for (int i = 0; i < listSize; i++)
        strm << left << setw(MAX_WIDTH) << setfill(separator) << ol.orders[i]->getLabel() << " | ";

    strm << "\n";

    return strm;
}

/**
 * Returns the label of the order.
 * @return
 */
string deploy::getLabel() const
{
    return label;
}

/**
 * Returns the label of the order.
 * @return
 */
string AdvanceOrder::advance::getLabel() const
{
    return label;
}

/**
 * Returns the label of the order.
 * @return
 */
string bomb::getLabel() const
{
    return label;
}

/**
 * Returns the label of the order.
 * @return
 */
string blockade::getLabel() const
{
    return label;
}

/**
 * Returns the label of the order.
 * @return
 */
string airlift::getLabel() const
{
    return label;
}

/**
 * Returns the label of the order.
 * @return
 */
string negotiate::getLabel() const
{
    return label;
}

/**
 * Works in conjunction with printOrder() from subclasses to polymorphically
 * give information about a specific order using cout.
 * @param strm
 * @param o
 * @return
 */
ostream &operator<<(ostream &strm, const Order &o)
{
    return o.printOrder(strm);
}

/**
 * Does not print anything useful for this assignment.
 * @param out
 * @return
 */
ostream &deploy::printOrder(ostream &out) const
{
    return out << "This is a deploy order!";
}

ostream &AdvanceOrder::advance::printOrder(ostream &out) const
{
    return out << "This is an advance order!";
}

ostream &bomb::printOrder(ostream &out) const
{
    return out << "This is a bomb order!";
}

ostream &blockade::printOrder(ostream &out) const
{
    return out << "This is a blockade order!";
}

ostream &airlift::printOrder(ostream &out) const
{
    return out << "This is an airlift order!";
}

ostream &negotiate::printOrder(ostream &out) const
{
    return out << "This is a negotiate order!";
}

/**
 * For this assignment, validation is not defined.
 * @return
 */
bool deploy::validate() const
{
    cout << "Validating Deploy...\n";

    if (target->getTerritoryPlayerID() != currentPlayer->getPlayerID())
    {
        cout << "You do not own this territory!\n"
             << endl;
        return false;
    }

    cout << "Your order has been validated!\n"
         << endl;

    return true;
}

bool AdvanceOrder::advance::validate() const
{
    cout << "Validating Advance...\n";

    if (source->getTerritoryPlayerID() != currentPlayer->getPlayerID())
    {
        cout << "The source territory is not your own!\n"
             << endl;
        return false;
    }

    else if (!source->isAdjacent(target))
    {
        cout << "The target territory is not adjacent to the source territory!\n"
             << endl;
        return false;
    }

    cout << "Your order has been validated!\n"
         << endl;

    return true;
}

bool bomb::validate() const
{
    cout << "Validating Bomb...\n";

    if (target->getTerritoryPlayerID() == currentPlayer->getPlayerID())
    {
        cout << "This territory is your own!\n"
             << endl;
        return false;
    }

    cout << "Your order has been validated!\n"
         << endl;

    return true;
}

bool blockade::validate() const
{
    cout << "Validating Blockade...\n";

    if (target->getTerritoryPlayerID() != currentPlayer->getPlayerID())
    {
        cout << "This is not your territory! This order can only be played on your own territory!\n"
             << endl;
        return false;
    }

    cout << "Your order has been validated!\n"
         << endl;

    return true;
}

bool airlift::validate() const
{
    cout << "Validating Airlift...\n";

    if (source->getTerritoryPlayerID() != currentPlayer->getPlayerID())
    {
        cout << "The source territory is not your own!\n"
             << endl;
        return false;
    }

    cout << "Your order has been validated!\n"
         << endl;

    return true;
}

bool negotiate::validate() const
{
    cout << "Validating Negotiate...\n";

    if (targetPlayer->getPlayerID() == currentPlayer->getPlayerID())
    {
        cout << "You cannot negotiate with yourself!\n"
             << endl;
        return false;
    }

    cout << "Your order has been validated!\n"
         << endl;

    return true;
}

/**
 * Validates an order and proceeds accordingly. For this assignment, execution is not defined.
 */
void deploy::execute() const
{
    if (validate())
    {
        cout << "Deploy is being executed!\n";
        target->setNumOfArmies(*amount + target->getNumOfArmies());
        cout << "Deploy has finished executing!\n"
             << endl;
    }
}

void AdvanceOrder::advance::execute() const
{
    if (validate())
    {
        cout << "Advance is being executed!\n";

        if (source->getTerritoryPlayerID() == target->getTerritoryPlayerID()) // Transferring army to another territory
        {
            source->setNumOfArmies(source->getNumOfArmies() - *amount);
            target->setNumOfArmies(target->getNumOfArmies() + *amount);
        }

        else // If you try to transfer on enemy territory, considered as attack.
        {
            if (!currentPlayer->canAttack(target->getTerritoryPlayerID()))
            {
                cout << "You cannot attack this player!\n"
                     << endl;
                return;
            }

            attackSimulation(source, target, currentPlayer, amount);
        }

        cout << "Advance has finished executing!\n"
             << endl;
    }
}

void bomb::execute() const
{
    if (validate())
    {
        if (!currentPlayer->canAttack(target->getTerritoryPlayerID()))
        {
            cout << "You cannot attack this player!\n"
                 << endl;
            return;
        }

        cout << "Bomb is being executed!\n"
             << endl;
        target->setNumOfArmies(target->getNumOfArmies() / 2);
        cout << "Bomb has finished executing!\n"
             << endl;
    }
}

void blockade::execute() const
{
    if (validate())
    {
        cout << "Blockade is being executed!\n";

        target->setNumOfArmies(target->getNumOfArmies() * 2);
        target->setTerritoryPlayerID(-1); // Transfer to neutral player.
    }
}

void airlift::execute() const
{
    if (validate())
    {
        if (!currentPlayer->canAttack(target->getTerritoryPlayerID()))
        {
            cout << "You cannot attack this player!\n"
                 << endl;
            return;
        }

        cout << "Airlift is being executed!\n";

        if (source->getTerritoryPlayerID() == target->getTerritoryPlayerID()) // Transferring army to another territory
        {
            source->setNumOfArmies(source->getNumOfArmies() - *amount);
            target->setNumOfArmies(target->getNumOfArmies() + *amount);
        }

        else // If you try to airlift on enemy territory, considered as attack.
        {
            attackSimulation(source, target, currentPlayer, amount);
        }

        cout << "Advance has finished executing!\n"
             << endl;
    }
}

void negotiate::execute() const
{
    if (validate())
    {
        cout << "Negotiate is being executed!\n";
        currentPlayer->addFriendly(targetPlayer->getPlayerID());
        targetPlayer->addFriendly(currentPlayer->getPlayerID());
    }

    cout << "Negotiate has finished executing!" << endl;
}

/**
 * Since we have a list of pointers to an abstract class,
 * we need a way to polymorphically clone the objects in the
 * list if we ever decide to deep-copy the list. Calls the
 * compiler-generated copy constructor, which is OK since
 * these subclasses don't have object specific data members.
 * @return
 */
Order *deploy::clone() const
{
    return new deploy(*this);
}

Order *AdvanceOrder::advance::clone() const
{
    return new advance(*this);
}

Order *bomb::clone() const
{
    return new bomb(*this);
}

Order *blockade::clone() const
{
    return new blockade(*this);
}

Order *airlift::clone() const
{
    return new airlift(*this);
}

Order *negotiate::clone() const
{
    return new negotiate(*this);
}

void attackSimulation(Territory *source, Territory *target, Player *currentPlayer, int *amount)
{
    source->setNumOfArmies(source->getNumOfArmies() - *amount); // Attackers leave home territory

    srand(time(NULL));
    int successAttack = 0;
    int successDefend = 0;

    int adversaryId;
    vector<Territory *> adversaryTerritories;
    vector<Territory *> adversaryDefendList;

    for (int i = 1; i <= *amount; i++) // Attacking Phase
    {
        int roll = rand() % 100 + 1;

        if (roll <= 60)
        {
            successAttack++;
        }
    }

    for (int i = 1; i <= target->getNumOfArmies(); i++) // Defending Phase
    {
        int roll = rand() % 100 + 1;

        if (roll <= 70)
        {
            successDefend++;
        }
    }

    int remainingAttackArmies = *amount - successDefend;
    int remainingDefendArmies = target->getNumOfArmies() - successAttack;

    if (remainingAttackArmies < 0) // Possible if for example 1 attacker vs 70 defenders
    {
        remainingAttackArmies = 0;
    }

    if (remainingDefendArmies < 0) // Possible if for example 1 defender vs 70 attackers
    {
        remainingDefendArmies = 0;
    }

    if (remainingAttackArmies > 0 && remainingDefendArmies == 0) // Win
    {
        cout << "Territory conquered! You have won this battle!\n"
             << endl;
        target->setTerritoryPlayerID(currentPlayer->getPlayerID()); // Current player now occupies territory
        currentPlayer->getTerritoryList()->push_back(target);       // territory added to player list
        currentPlayer->getDefendList()->push_back(target);          // add territory to the defendList of the player
        adversaryId = currentPlayer->getGE()->getMap()->getTerritoryById(target->getTerritoryID())->getTerritoryPlayerID();
        adversaryTerritories = *currentPlayer->getGE()->getPlayerByID(adversaryId)->getTerritoryList();
        adversaryTerritories.erase(remove(adversaryTerritories.begin(), adversaryTerritories.end(), target), adversaryTerritories.end()); // removed from territoryList of adversary
        adversaryDefendList = *currentPlayer->getGE()->getPlayerByID(adversaryId)->getDefendList();
        adversaryDefendList.erase(remove(adversaryDefendList.begin(), adversaryDefendList.end(), target), adversaryDefendList.end()); // remove from defendList of adversary
        target->setNumOfArmies(remainingAttackArmies);                                                                                // Attackers advance to conquered territory
        currentPlayer->getGE()->Notify();                                                                                             // Notify stats observer since a player conquered a territory
    }

    else // Lose. A draw is considered a loss. If any, attackers retreat. If any, defenders retreat.
    {
        cout << "Territory has not been conquered. You have lost this battle!\n"
             << endl;
        source->setNumOfArmies(source->getNumOfArmies() + remainingAttackArmies); // Attackers retreat
        target->setNumOfArmies(remainingDefendArmies);
    }

    if (source->getNumOfArmies() == 0)
    {
        cout << "The attacker has lost his territory in the process!\n"
             << endl;
        source->setTerritoryPlayerID(-1);
    }

    if (target->getNumOfArmies() == 0)
    {
        cout << "The defender has lost his territory in the process!\n"
             << endl;
        target->setTerritoryPlayerID(-1);
    }
}
