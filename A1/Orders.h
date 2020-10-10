#pragma once
#include<vector> // To implement a list containing orders.
#include<iostream> // For input/output.
#include<iomanip> // To format output.
#include<string> // To store the label of an order within the order object itself.

using std::cout;
using std::endl;
using std::vector;
using std::ostream;
using std::setw;
using std::setfill;
using std::left;
using std::string;

// This is an abstract class for orders. All functionalities meant
// to be implemented by subclasses.
class Order
{
public:
	virtual string getLabel() const = 0;
	virtual bool validate() = 0;
	virtual void execute() = 0;
	virtual ~Order() = 0;

private:
	virtual Order* clone() const = 0;
	virtual ostream& printOrder(ostream&) const = 0;

	friend ostream& operator<<(ostream&, const Order&);
	friend class OrdersList;
};

class deploy : public Order
{
public:

	string getLabel() const override;
	bool validate() override;
	void execute() override;
	~deploy();

private:
	const string label = "deploy";
	Order* clone() const override;
	ostream& printOrder(ostream&) const override;
};


class advance : public Order
{
public:
	string getLabel() const override;
	bool validate() override;
	void execute() override;
	~advance();

private:
	const string label = "advance";
	Order* clone() const override;
	ostream& printOrder(ostream&) const override;
};

class bomb : public Order
{
public:
	string getLabel() const override;
	bool validate() override;
	void execute() override;
	~bomb();

private:
	const string label = "bomb";
	Order* clone() const override;
	ostream& printOrder(ostream&) const override;
};

class blockade : public Order
{
public:
	string getLabel() const override;
	bool validate() override;
	void execute() override;
	~blockade();

private:
	const string label = "blockade";
	Order* clone() const override;
	ostream& printOrder(ostream&) const override;
};

class airlift : public Order
{
public:
	string getLabel() const override;
	bool validate() override;
	void execute() override;
	~airlift();

private:
	const string label = "airlift";
	Order* clone() const override;
	ostream& printOrder(ostream&) const override;
};

class negotiate : public Order
{
public:
	string getLabel() const override;
	bool validate() override;
	void execute() override;
	~negotiate();

private:
	const string label = "negotiate";
	Order* clone() const override;
	ostream& printOrder(ostream&) const override;
};

// Should be created at the beginning of the program.
// Creates an order, the type depending on the user input.
class OrderFactory
{
public:
	Order* createOrder(string) const;
};


// Designed to hold a list of valid orders
// and carry out basic list functions.
class OrdersList
{
    public:
	    OrdersList();
	    ~OrdersList();
	    OrdersList(const OrdersList&);

	    vector<Order*>* getListOfOrders();
	    void addOrder(Order* o);
	    void deleteOrder(int);
	    void moveOrder(int, int);
	    OrdersList& operator=(const OrdersList&);
        int listSize();

    private:
	    vector<Order*>* orders;
	    friend ostream& operator<<(ostream&, const OrdersList&);
};
