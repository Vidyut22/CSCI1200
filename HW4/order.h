#ifndef Order_h_
#define Order_h_
using namespace std;
#include <iostream>
#include <string>
#include <list>
class Order
{
public:
	//CONSTRUCTOR, DESTRUCTOR
	Order(int id, int time, int numItems, list<string>items);
	~Order();
	//MEMBER FUNCTIONS AND OTHER OPERATORS
	
	//ACCESSORS
	int getId() const;
	int getTimeRemaining() const;
	int getNumItems() const;
	list<string>getItems() const;
	//MODIFIERS
	void updateTimeRemaining();
private:
	//REPRESENTATION
	int id; // Id of Order
	int time; // Time Remaining till Order Expires
	int numItems; // Number of Items in Order
	list<string>items; // List of Items in Order
};
// HELPER METHODS
bool sortOrders(const Order& o1, const Order& o2); //Sort based on time
bool sortOrdersID(const Order& o1, const Order& o2);//Sort based on ID
void printOrders(list<Order> orders); //Print all items in all orders
#endif