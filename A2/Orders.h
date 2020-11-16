#pragma once
#include <vector> // To implement a list containing orders.
#include <string> // To store the label of an order within the order object itself.
#include <iostream>

using std::vector;
using std::string;
using std::ostream;

class Player;
class Territory;

/**
 * This is an abstract class for orders. All functionalities meant to be implemented by subclasses.
 */



class Order // ORDER MIGHT NEED ID IN THE FUTURE
{
public:
    virtual string getLabel() const = 0;

    virtual bool validate() const = 0;

    virtual void execute() const = 0;

    Order();

    explicit Order(Player &);

    virtual ~Order() = 0;

protected:
    Player *currentPlayer;
    bool enabled;

private:
    virtual Order *clone() const = 0;

    virtual ostream &printOrder(ostream &) const = 0;

    friend ostream &operator<<(ostream &, const Order &);

    friend class OrdersList;
};

class deploy : public Order {
public:
    deploy();

    deploy(Territory &, Player &, int); // Target territory, current player, amount
    ~deploy() override;

    string getLabel() const override;

    bool validate() const override;

    void execute() const override;

private:
    const static string label;

    Order *clone() const override;

    ostream &printOrder(ostream &) const override;

    Territory *target; // Target territory to deploy at
    int *amount; // Amount of armies to deploy
};

namespace AdvanceOrder
{
    class advance : public Order {
    public:
        advance();

        advance(Territory &, Territory &, Player &, int); // Src, dest, current player, amount
        ~advance() override;

        string getLabel() const override;

        bool validate() const override;

        void execute() const override;

    private:
        const static string label;

        Order *clone() const override;

        ostream &printOrder(ostream &) const override;

        Territory *source;
        Territory *target;
        int *amount;
    };
}

class bomb : public Order {
public:
    bomb();

    bomb(Territory &, Player &); // Target territory to bomb, current player
    ~bomb() override;

    string getLabel() const override;

    bool validate() const override;

    void execute() const override;

private:
    const static string label;

    Order *clone() const override;

    ostream &printOrder(ostream &) const override;

    Territory *target;
};

class blockade : public Order {
public:
    blockade();

    blockade(Territory &, Player &); // Target, current player
    ~blockade() override;

    string getLabel() const override;

    bool validate() const override;

    void execute() const override;

private:
    const static string label;

    Order *clone() const override;

    ostream &printOrder(ostream &) const override;

    Territory *target;
};

class airlift : public Order {
public:
    airlift();

    airlift(Territory &, Territory &, Player &, int); // Source, target, current player, amount
    ~airlift() override;

    string getLabel() const override;

    bool validate() const override;

    void execute() const override;

private:
    const static string label;

    Order *clone() const override;

    ostream &printOrder(ostream &) const override;

    Territory *source;
    Territory *target;
    int *amount;
};

class negotiate : public Order {
public:
    negotiate();

    negotiate(Player &, Player &);

    ~negotiate() override;

    string getLabel() const override;

    bool validate() const override;

    void execute() const override;

private:
    const static string label;

    Order *clone() const override;

    ostream &printOrder(ostream &) const override;

    Player *targetPlayer;
};

/**
* Should be created at the beginning of the program.
* Creates an order, the type depending on the user input.
*/
/*class OrderFactory {
public:
    Order *createOrder(const string&, Territory*, Territory*, Player*, Player*, int*) const;
};*/

/**
* Designed to hold a list of valid orders
* and carry out basic list functions.
*/
class OrdersList {
public:
    OrdersList();

    ~OrdersList();

    OrdersList(const OrdersList &);

    void addOrder(Order *o);

    void deleteOrder(int);

    void moveOrder(int, int);

    void executeOrders(); // Executes orders and empties the list
    OrdersList &operator=(const OrdersList &);

    int getOrdersListSize();

    Order *getOrder(int index);

private:
    vector<Order *> orders;

    friend ostream& operator<<(ostream&, const OrdersList&);
};

void attackSimulation(Territory*, Territory*, Player*, int*);



