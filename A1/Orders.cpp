#include "Orders.h"

// The labels of the orders, which are constant and static.
const string deploy::label = "Deploy";
const string advance::label = "Advance";
const string bomb::label = "Bomb";
const string blockade::label = "Blockade";
const string airlift::label = "Airlift";
const string negotiate::label = "Negotiate";

OrdersList::OrdersList()
{

}

OrdersList::~OrdersList()
{
	int listSize = orders.size();

	for (int i = 0; i < listSize; i++) // Delete memory for orders, which are always dynamically allocated.
		delete orders[i];
}

// Makes a deep-copy of a list.
OrdersList::OrdersList(const OrdersList& oldList)
{
	int listSize = oldList.orders.size();
	orders = vector<Order*>(listSize);

	for (int i = 0; i < listSize; i++) // Same objects, but in different memory locations.
		orders[i] = oldList.orders[i]->clone();

	cout << "The list has been copied!" << endl;
}

Order::~Order()
{

}

deploy::~deploy()
{

}

advance::~advance()
{

}

bomb::~bomb()
{

}

blockade::~blockade()
{

}

airlift::~airlift()
{

}

negotiate::~negotiate()
{

}

void OrdersList::addOrder(Order* o)
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

void OrdersList::deleteOrder(int pos)
{
	int listSize = orders.size();

	if (listSize == 0) // Empty list so nothing to be done.
		cout << "Nothing to erase!" << endl;
	else if (pos > listSize || pos < 1) // Bounds check.
		cout << "Please select a valid position!" << endl;
	else
	{
		delete orders[pos - 1]; // Order objects are dynamically allocated, so frees memory.
		orders.erase(orders.begin() + pos - 1); // Once memory freed, delete actual pointer from list.
		cout << "Erase at position " << pos << " successful! Your list now looks like: \n";
		cout << *this << endl;
	}
}

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
		Order* temp = orders[pos1 - 1]; // Swap pointers. Address of actual object unchanged.
		orders[pos1 - 1] = orders[pos2 - 1];
		orders[pos2 - 1] = temp;
		cout << "Order " << pos1 << " and Order " << pos2 << " have been swapped! Your list now looks like: \n";
		cout << *this << endl;
	}
}

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

OrdersList& OrdersList::operator=(const OrdersList& rhsList) // Releases resources by LHS and deep-copy
{                                                            // to RHS
	int listSize = rhsList.orders.size();

	if (&rhsList == this) // Checks for self assignment
		return *this;

	this->~OrdersList(); // Deallocate dynamic memory of LHS
	this->orders = vector<Order*>(listSize); // Reallocate memory for vector of size RHS

	for(int i = 0; i < listSize; i++)
		this->orders[i] = rhsList.orders[i]->clone(); // Clone RHS element into LHS

	return *this;
}

// Prints the list using cout.
ostream& operator<<(ostream& strm, const OrdersList& ol)
{
	int listSize = ol.orders.size(); // For iteration
	const int MAX_WIDTH = 9; // To force the amount of space a string takes.
	const char separator = ' '; // If string.length() < 9, fill with empty spaces.

	for (int i = 0; i < listSize; i++)
		strm << left << setw(MAX_WIDTH) << setfill(separator) << i + 1 << " | "; // Left formatted

	strm << "\n";

	for (int i = 0; i < listSize; i++)
		strm << left << setw(MAX_WIDTH) << setfill(separator) << ol.orders[i]->getLabel() << " | ";

	strm << "\n";

	return strm;
}

// Returns the label of the order.
string deploy::getLabel() const
{
	return label;
}

string advance::getLabel() const
{
	return label;
}

string bomb::getLabel() const
{
	return label;
}

string blockade::getLabel() const
{
	return label;
}

string airlift::getLabel() const
{
	return label;
}

string negotiate::getLabel() const
{
	return label;
}

// Works in conjunction with printOrder() from subclasses to polymorphically
// give information about a specific order using cout.
ostream& operator<<(ostream& strm, const Order& o)
{
	return o.printOrder(strm);
}

// Does not print anything useful for this assignment.
ostream& deploy::printOrder(ostream& out) const
{
	return out << "This is a deploy order!";
}

ostream& advance::printOrder(ostream& out) const
{
	return out << "This is an advance order!";
}

ostream& bomb::printOrder(ostream& out) const
{
	return out << "This is a bomb order!";
}

ostream& blockade::printOrder(ostream& out) const
{
	return out << "This is a blockade order!";
}

ostream& airlift::printOrder(ostream& out) const
{
	return out << "This is an airlift order!";
}

ostream& negotiate::printOrder(ostream& out) const
{
	return out << "This is a negotiate order!";
}

// For this assignment, validation is not defined.
bool deploy::validate() const
{
	cout << "Validating Deploy...\n";
	return true;
}

bool advance::validate() const
{
	cout << "Validating Advance...\n";
	return true;
}

bool bomb::validate() const
{
	cout << "Validating Bomb...\n";
	return true;
}

bool blockade::validate() const
{
	cout << "Validating Blockade...\n";
	return true;
}

bool airlift::validate() const
{
	cout << "Validating Airlift...\n";
	return true;
}

bool negotiate::validate() const
{
	cout << "Validating Negotiate...\n";
	return true;
}

// Validates an order and proceeds accordingly. For this assignment, execution
// is not defined.
void deploy::execute() const
{
	if (validate())
		cout << "Deploy is being executed!/n";
}

void advance::execute() const
{
	if (validate())
		cout << "Advance is being executed!\n";
}

void bomb::execute() const
{
	if (validate())
		cout << "Bomb is being executed!\n";
}

void blockade::execute() const
{
	if (validate())
		cout << "Blockade is being executed!\n";
}

void airlift::execute() const
{
	if (validate())
		cout << "Airlift is being executed!\n";
}

void negotiate::execute() const
{
	if (validate())
		cout << "Negotiate is being executed!\n";
}

// Since we have a list of pointers to an abstract class,
// we need a way to polymorphically clone the objects in the
// list if we ever decide to deep-copy the list. Calls the
// compiler-generated copy constructor, which is OK since
// these subclasses don't have object specific data members.
Order* deploy::clone() const
{
	return new deploy(*this);
}                             

Order* advance::clone() const
{
	return new advance(*this);
}

Order* bomb::clone() const
{
	return new bomb(*this);
}

Order* blockade::clone() const
{
	return new blockade(*this);
}

Order* airlift::clone() const
{
	return new airlift(*this);
}

Order* negotiate::clone() const
{
	return new negotiate(*this);
}

// Creates an order based on user input. Only the strings below
// are the possible orders in this game. If the user inputs a
// string different than those listed, it returns a null pointer,
// which is meant to be handled in OrdersList::addOrder().
Order* OrderFactory::createOrder(string orderType) const
{
	if (orderType == "deploy")
		return new deploy;
	else if (orderType == "advance")
		return new advance;
	else if (orderType == "bomb")
		return new bomb;
	else if (orderType == "blockade")
		return new blockade;
	else if (orderType == "airlift")
		return new airlift;
	else if (orderType == "negotiate")
		return new negotiate;
	else
		return nullptr;
}