using namespace std;
#include "Query.h"

/*
Method to return the hash value of given query.
Overview: If category is valid, add it to a string
After all categories added to string, loop thru
ascii values of categories and keep a running integer
of ascii int powers along with bit shifting
*/
 unsigned int Query::hash()
{
   //  This implementation comes from 
   //  http://www.partow.net/programming/hashfunctions/
   //
   //  This is a general-purpose, very good hash function for strings.

	unsigned int hash = 1315423911;
	string totalQuery = "";

	//If valid category, add it to totalQuery string
	if (title != "?")
	{
		totalQuery += title;
	}
	if (year != "?")
	{
		totalQuery += year;
	}
	if (runtime != "?")
	{
		totalQuery += runtime;
	}
	if(genres.size()!=0)
	{
		totalQuery += to_string(genres.size());
		for (unsigned int i = 0; i < genres.size(); i++)
		{
			totalQuery += genres[i];
		}
	}
	if (actors.size() != 0)
	{
		totalQuery += to_string(actors.size());
		for (unsigned int i = 0; i < actors.size(); i++)
		{
				totalQuery += actors[i];
		}
	}
	if (roles.size() != 0)
	{
		totalQuery += to_string(roles.size());
		for (unsigned int i = 0; i < roles.size(); i++)
		{
			totalQuery += roles[i];
		}
	}
	//Loop thru all characters
	for (unsigned int i = 0; i < totalQuery.size(); i++)
	{
		//Keep a running exponent by bitshifting ascii value
		hash ^= ((hash << 5) + totalQuery[i] + (hash >> 2));
	}
	return hash;
	
}
 /*
 Overload == operator for queries
 */
bool Query::operator==(const Query& q2) const
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

/*
Overload != operator for queries
*/
bool Query::operator!=(const Query& q2) const
{
	if (title != q2.title)
	{
		return true;
	}
	if (year != q2.year)
	{
		return true;
	}
	if (runtime != q2.runtime)
	{
		return true;
	}
	if (genres != q2.genres)
	{
		return true;
	}
	if (actors != q2.actors)
	{
		return true;
	}
	if (roles != q2.roles)
	{
		return true;
	}
	return false;
}