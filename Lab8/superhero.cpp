#include <string>
#include <iostream>
#include <sstream>
#include <cassert>
#include "superhero.h"
using namespace std;

Superhero::Superhero(string supername, string name, string power)
{
	this->supername = supername;
	this->name = name;
	this->power = power;
	good = true;
}

string Superhero::getName()
{
	return supername;
}

string Superhero::getPower()
{
	return power;
}

bool Superhero::operator==(string str)
{
	return str == name;
}

bool Superhero::operator!=(string str)
{
	return str != name;
}
string Superhero::getTrueIdentity()
{
	return name;
}
bool Superhero::isGood()
{
	return good;
}

void Superhero::operator-()
{
	good = !good;
}
ostream& operator<<(ostream& os, Superhero& superhero)
{
	os << "Superhero " << superhero.getName() << " has power " << superhero.getPower() << endl;
	return os;
}
bool Superhero::operator>(const Superhero& superhero)
{
	if (superhero.power == "Flexible")
	{
		if (power == "Flexible")
		{
			return false;
		}
		else if (power == "Flying")
		{
			return false;
		}
		else if (power == "Invisible")
		{
			return true;
		}
		else if (power == "Laser")
		{
			return true;
		}
		else if (power == "Fire")
		{
			return true;
		}
		else if (power == "Wood")
		{
			return false;
		}
		else if (power == "Water")
		{
			return false;
		}
		else if (power == "Speed")
		{
			return true;
		}
	}
	else if (superhero.power == "Flying")
	{
		if (power == "Flexible")
		{
			return true;
		}
		else if (power == "Flying")
		{
			return false;
		}
		else if (power == "Invisible")
		{
			return true;
		}
		else if (power == "Laser")
		{
			return true;
		}
		else if (power == "Fire")
		{
			return false;
		}
		else if (power == "Wood")
		{
			return false;
		}
		else if (power == "Water")
		{
			return false;
		}
		else if (power == "Speed")
		{
			return false;
		}
	}
	else if (superhero.power == "Invisible")
	{
		if (power == "Flexible")
		{
			return false;
		}
		else if (power == "Flying")
		{
			return false;
		}
		else if (power == "Invisible")
		{
			return true;
		}
		else if (power == "Laser")
		{
			return true;
		}
		else if (power == "Fire")
		{
			return false;
		}
		else if (power == "Wood")
		{
			return false;
		}
		else if (power == "Water")
		{
			return true;
		}
		else if (power == "Speed")
		{
			return false;
		}
	}
	else if (superhero.power == "Laser")
	{
		if (power == "Flexible")
		{
			return false;
		}
		else if (power == "Flying")
		{
			return false;
		}
		else if (power == "Invisible")
		{
			return false;
		}
		else if (power == "Laser")
		{
			return false;
		}
		else if (power == "Fire")
		{
			return true;
		}
		else if (power == "Wood")
		{
			return false;
		}
		else if (power == "Water")
		{
			return true;
		}
		else if (power == "Speed")
		{
			return true;
		}
	}
	else if (superhero.power == "Fire")
	{
	if (power == "Flexible")
	{
		return false;
	}
	else if (power == "Flying")
	{
		return true;
	}
	else if (power == "Invisible")
	{
		return true;
	}
	else if (power == "Laser")
	{
		return false;
	}
	else if (power == "Fire")
	{
		return false;
	}
	else if (power == "Wood")
	{
		return false;
	}
	else if (power == "Water")
	{
		return true;
	}
	else if (power == "Speed")
	{
		return true;
	}
	}
	else if (superhero.power == "Wood")
	{
	if (power == "Flexible")
	{
		return true;
	}
	else if (power == "Flying")
	{
		return true;
	}
	else if (power == "Invisible")
	{
		return true;
	}
	else if (power == "Laser")
	{
		return true;
	}
	else if (power == "Fire")
	{
		return true;
	}
	else if (power == "Wood")
	{
		return false;
	}
	else if (power == "Water")
	{
		return false;
	}
	else if (power == "Speed")
	{
		return false;
	}
	}
	else if (superhero.power == "Water")
	{
	if (power == "Flexible")
	{
		return true;
	}
	else if (power == "Flying")
	{
		return true;
	}
	else if (power == "Invisible")
	{
		return false;
	}
	else if (power == "Laser")
	{
		return false;
	}
	else if (power == "Fire")
	{
		return false;
	}
	else if (power == "Wood")
	{
		return true;
	}
	else if (power == "Water")
	{
		return false;
	}
	else if (power == "Speed")
	{
		return true;
	}
	}
	else if (superhero.power == "Speed")
	{
	if (power == "Flexible")
	{
		return false;
	}
	else if (power == "Flying")
	{
		return true;
	}
	else if (power == "Invisible")
	{
		return true;
	}
	else if (power == "Laser")
	{
		return false;
	}
	else if (power == "Fire")
	{
		return false;
	}
	else if (power == "Wood")
	{
		return true;
	}
	else if (power == "Water")
	{
		return false;
	}
	else if (power == "Speed")
	{
		return false;
	}
	}
	return false;
	
}