using namespace std;
#include <string>
#include <list>
#include "item.h"

//Default Constructor, assign all representation values
Item::Item(int time, string item)
{
	this->time = time;
	this->item = item;
}
//Return Item Name
string Item::getItem() const
{
	return item;
}
//Return Time to Cook Item
int Item::getTime() const
{
	return time;
}
//Update Time Left to Cook by 1
void Item::updateTime()
{
	time--;
}
//Helper method to sort items based on time to cook and then item name
bool sortItems(const Item& i1, const Item& i2)
{
	if (i1.getTime() == i2.getTime())
	{
		return i1.getItem() < i2.getItem();
	}
	else
	{
		return i1.getTime() < i2.getTime();
	}
}