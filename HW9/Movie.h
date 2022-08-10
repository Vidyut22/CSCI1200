#pragma once
#include <iostream>
#include <list>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
class Movie
{
public:
	//CONSTRUCTOR
	Movie() {}

	//SETTERS
	void setTitle(string title)
	{
		this->title = title;
	}
	void setYear(string year)
	{
		this->year = year;
	}
	void setRunTime(string runtime)
	{
		this->runtime = runtime;
	}
	void setGenres(vector<string> genres)
	{
		this->genres = genres;
	}
	void setActors(vector<string> actors)
	{
		this->actors = actors;
	}
	void setRoles(vector<string> roles)
	{
		this->roles = roles;
	}

	//ACCESSORS
	string getTitle()
	{
		return title;
	}
	string getYear()
	{
		return year;
	}
	string getRunTime()
	{
		return runtime;
	}
	vector<string> getGenres()
	{
		return genres;
	}
	vector<string> getActors()
	{
		return actors;
	}
	vector<string> getRoles()
	{
		return roles;
	}

	//HELPER METHODS
	//Method to clear all member variables of Movie
	void clear()
	{
		title.clear();
		year.clear();
		runtime.clear();
		genres.clear();
		actors.clear();
		roles.clear();
	}
	//OVERLOAD
	bool operator==(const Movie& q2) const;
private:
	//PRIVATE MEMBER VARIABLES
	string title;
	string year;
	string runtime;
	vector<string> genres;
	vector<string> actors;
	vector<string> roles;
};