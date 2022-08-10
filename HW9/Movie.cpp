#include <iostream>
#include <list>
#include <string>
#include <vector>
#include <algorithm>
#include "Movie.h"
using namespace std;

/*
Overload == operator for queries
*/
bool Movie::operator==(const Movie& q2) const
{
	if (title != q2.title)
	{
		return false;
	}
	if (year != q2.year)
	{
		return false;
	}
	if (runtime != q2.runtime)
	{
		return false;
	}
	if (genres != q2.genres)
	{
		return false;
	}
	if (actors != q2.actors)
	{
		return false;
	}
	if (roles != q2.roles)
	{
		return false;
	}
	return true;
}