using namespace std;
#include <string>
#include <list>
#include "order.h"

//Default Constructor, assign all representation values
Order::Order(int id, int time, int numItems, list<string>items)
{
	this->id = id;
	this->time = time;
	this->numItems = numItems;
	this->items = items;
}
//Delete Items
Order::~Order()
{
	items.clear();
}
//Return Order ID
int Order::getId() const
{
	return id;
}
//Return Time Remaining on Order
int Order::getTimeRemaining() const
{
	return time;
}
//Return Number of Items in Order
int Order::getNumItems() const
{
	return numItems;
}
//Return List of All Items in Order
list<string> Order::getItems() const
{
	return items;
}
//Update Time Remaining by 1
void Order::updateTimeRemaining()
{
	time--;
}
//Helper method to sort orders based on shortest time remaining and then by ID
bool sortOrders(const Order& o1, const Order& o2)
{
	if (o1.getTimeRemaining() == o2.getTimeRemaining())
	{
		return o1.getId() < o2.getId();
	}
	else
	{
		return o1.getTimeRemaining() < o2.getTimeRemaining();
	}
}
//Helper method to sort orders based on ID
bool sortOrdersID(const Order& o1, const Order& o2)
{
	return o1.getId() < o2.getId();
}
//Helper method to print all items in each order
void printOrders(list<Order> orders)
{
	//Loop through Orders
	for (list<Order>::iterator i = orders.begin(); i != orders.end(); i++)
	{
		cout << "  #" << (*i).getId() << " (" << (*i).getTimeRemaining() << " minute(s) left):" << endl;
		list<string> currItems = (*i).getItems();
		//Loop through Items
		for (list<string>::iterator j = currItems.begin(); j != currItems.end(); j++)
		{
			cout << "    " << *j << endl;
		}
	}
}