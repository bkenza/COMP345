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
class Order // ORDER MIGHT NEED ID IN THE FUTURE
{
public:
	virtual string getLabel() const = 0;
	virtual bool validate() const = 0;
	virtual void execute() const = 0;
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
	bool validate() const override;
	void execute() const override;
	~deploy();

private:
	const static string label;
	Order* clone() const override;
	ostream& printOrder(ostream&) const override;
};


class advance : public Order
{
public:
	string getLabel() const override;
	bool validate() const override;
	void execute() const override;
	~advance();

private:
	const static string label;
	Order* clone() const override;
	ostream& printOrder(ostream&) const override;
};

class bomb : public Order
{
public:
	string getLabel() const override;
	bool validate() const override;
	void execute() const override;
	~bomb();

private:
	const static string label;
	Order* clone() const override;
	ostream& printOrder(ostream&) const override;
};

class blockade : public Order
{
public:
	string getLabel() const override;
	bool validate() const override;
	void execute() const override;
	~blockade();

private:
	const static string label;
	Order* clone() const override;
	ostream& printOrder(ostream&) const override;
};

class airlift : public Order
{
public:
	string getLabel() const override;
	bool validate() const override;
	void execute() const override;
	~airlift();

private:
	const static string label;
	Order* clone() const override;
	ostream& printOrder(ostream&) const override;
};

class negotiate : public Order
{
public:
	string getLabel() const override;
	bool validate() const override;
	void execute() const override;
	~negotiate();

private:
	const static string label;
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
	void addOrder(Order* o);
	void deleteOrder(int);
	void moveOrder(int, int);
	void executeOrders(); // Executes orders and empties the list
	OrdersList& operator=(const OrdersList&);

private:
	vector<Order*> orders;

	friend ostream& operator<<(ostream&, const OrdersList&);
};