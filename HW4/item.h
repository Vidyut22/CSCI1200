#ifndef Item_h_
#define Item_h_
using namespace std;
#include <iostream>
#include <string>
#include <list>
class Item
{
public:
	//CONSTRUCTOR
	Item(int time, string item);
	//MEMBER FUNCTIONS AND OTHER OPERATORS

	//ACCESSORS
	string getItem() const;
	int getTime() const;
	//MODIFIERS
	void updateTime();
private:
	//REPRESENTATION
	int time; // Amount of time to cook item
	string item; // Item name
};
//HELPER METHODS
bool sortItems(const Item& i1, const Item& i2); //Sort items based on time
#endif