#include <iostream>
#include <fstream>
#include <cassert>
#include <vector>
#include <string>
#include <iomanip>
#include <cmath>
#include <cstdlib>
#include "Course.h" //Include header file
using namespace std;
Course::Course(int CRN, string DEP, string COURSENUM, string COURSE, char DAY, string STIME, string eTIME, string ROOM) //Implementation of default Course object constructor
{
	crn = CRN; //Set crn to given crn
	dep = DEP; //Set department to given department
	courseNum = COURSENUM;//Set course number to given course number
	course = COURSE; // Set course name to given course name
	day = DAY; // Set day to given day
	stime = STIME; // Set starting time to given starting time
	etime = eTIME;// Set end time to given end time
	room = ROOM; //Set room to given room
}
//Implementation of accessor methods
int Course::getCRN() const
{
	return crn; //return crn number
}
string Course::getDep() const
{
	return dep; //return the department name
}
string Course::getcourseNum() const
{
	return courseNum; //return the course number
}
string Course::getCourse() const
{
	return course; // return course name
}
string Course::getDay() const //This accessor method returns full string name of day even though Course only has character of day
{
	vector<string> days = {"Monday", "Tuesday", "Wednesday", "Friday"}; // Initialize vectors of all days besides thursday (because first character of thursday doesn't match up)
	if (day != 'R') //Check if it is not thursday
	{
		for (int i = 0; i < (int)days.size(); i++) //Loop through all days
		{
			if (days[i][0] == day) //If the first index of the current day matches up with the days character of course
			{
				return days[i]; //return the current day
			}
		}
	}
	else
	{
		return "Thursday"; //If the character is R, return day as thursday
	}
	return " "; //Have to return to avoid warning, but will never reach
}
string Course::getSTime() const
{
	return stime; //return starting time
}
string Course::getETime() const
{
	return etime; //return end time
}
string Course::getRoom() const
{
	return room; //return name of the room
}
int leadTimeZero(string str)//Helper method to handle converting times into integers (ex. 03:00PM ->want to turn the 03 into just 3)
{
	if (str[0] == '0') //Check if the first character is 0
	{
		return str[1] - '0'; //Only return second character if first is equal to 0 (char - '0' converts character to int)
	}
	else
	{
		return stoi(str); //If not 0 return full string as an int
	}
}

bool roomSort(const Course& c1, const Course& c2) // Sorting method if the user selected mode is room
{
	if (c1.getRoom() == c2.getRoom()) //First order of rank (check if the room names are the same)
	{
		if (c1.getDay() == c2.getDay()) // Second order of rank (Check if the days are the same)
		{
			if (c1.getSTime() == c2.getSTime()) //Third order of rank (Check if the start times are the same)
			{
				if (c1.getcourseNum() == c2.getcourseNum()) //Fourth order of rank (check if the course numbers are the same)
				{
					return c1.getDep() < c2.getDep(); //Fifth order of rank (last check so simply return if course 1s department name is alphabetically before course 2's department name)
				}
				else
				{
					return c1.getcourseNum() < c2.getcourseNum(); //Return if course 1s course number is less than course 2s course number
				}
			}
			else //If start times are not the same rank ocordingly
			{
				int time1 = leadTimeZero(c1.getSTime().substr(0, 2)) * 60 + leadTimeZero(c1.getSTime().substr(3, 2)); //Convert first time in terms of minutes (AM/PM dealt with later)
				int time2 = leadTimeZero(c2.getSTime().substr(0, 2)) * 60 + leadTimeZero(c2.getSTime().substr(3, 2));//Convert second time in terms of minutes (AM/PM dealt with later)
				if (c1.getSTime().substr(5, 2) == "PM" && c1.getSTime().substr(0, 2)!="12") //If course 1's time is PM and the hour is not 12 (if it is 12, pm is already acounted for by the hour being 12)
				{
					time1 += 12 * 60; //add 12 hours worth of minutes to account for it being pm
				}
				if (c2.getSTime().substr(5, 2) == "PM" && c2.getSTime().substr(0, 2) != "12") //If course 2's time is PM and the hour is not 12 (if it is 12, pm is already acounted for by the hour being 12)
				{
					time2 += 12 * 60; //add 12 hours worth of minutes to account for it being pm
				}
				if (c1.getSTime().substr(0, 2) == "12" && c1.getSTime().substr(5, 2) == "AM") // //If course 1's time is AM  and the hour is 12 (if it is not 12, time starts from 01 chronologically so subtracting is uneeded)
				{
					time1 -= 12 * 60; //Subtract 12 hours worth of minutes to account for it being the beggining of am
				}
				if (c2.getSTime().substr(0, 2) == "12" && c2.getSTime().substr(5, 2) == "AM")// //If course 2's time is AM  and the hour is 12 (if it is not 12, time starts from 01 chronologically so subtracting is uneeded)
				{
					time2 -= 12 * 60;//Subtract 12 hours worth of minutes to account for it being the beggining of am
				}				
				return time1 < time2; //return if time1 is less than time 2
			}
		}
		else //If the days are not the same rank ocordingly 
		{
			vector<string>days = { "Monday", "Tuesday", "Wednesday","Thursday","Friday" }; //Initialize vector of all possible days
			int c1Day, c2Day; //Create 2 int variable to store indecies of the days
			for (int i = 0; i < (int)days.size(); i++) //Loop through all days
			{
				if (c1.getDay() == days[i])
				{
					c1Day = i; // If reached day in vector record index
				}
				else if (c2.getDay() == days[i])
				{
					c2Day = i; // If reached day in vector record index
				}
			}
			return c1Day < c2Day; //Return if first index is smaller than second (Indecies are in order of days of week)
		}
	}
	else //If the room names are not the same, return if the first courses room is alphabetically higher up
	{
		return c1.getRoom() < c2.getRoom(); //String comparison works for alphabetization
	}
}

bool depSort(const Course& c1, const Course& c2) //Sorting method if the user selected mode is dept
{
	if (c1.getcourseNum() == c2.getcourseNum()) //First order of rank (check if the course numbers are the same)
	{
		if (c1.getDay() == c2.getDay()) //Second order of rank (check if the days are the same)
		{
			//If days are the same return which time starts latest (last check)
			int time1 = leadTimeZero(c1.getSTime().substr(0, 2)) * 60 + leadTimeZero(c1.getSTime().substr(3, 2));//Convert first time in terms of minutes (AM/PM dealt with later)
			int time2 = leadTimeZero(c2.getSTime().substr(0, 2)) * 60 + leadTimeZero(c2.getSTime().substr(3, 2));//Convert second time in terms of minutes (AM/PM dealt with later)
			if (c1.getSTime().substr(5, 2) == "PM" && c1.getSTime().substr(0, 2) != "12") //If course 1's time is PM and the hour is not 12 (if it is 12, pm is already acounted for by the hour being 12)
			{
				time1 += 12 * 60;//add 12 hours worth of minutes to account for it being pm
			}
			if (c2.getSTime().substr(5, 2) == "PM" && c2.getSTime().substr(0, 2) != "12")//If course 2's time is PM and the hour is not 12 (if it is 12, pm is already acounted for by the hour being 12)
			{
				time2 += 12 * 60;//add 12 hours worth of minutes to account for it being pm
			}
			if (c1.getSTime().substr(0, 2) == "12" && c1.getSTime().substr(5, 2) == "AM")// //If course 1's time is AM  and the hour is 12 (if it is not 12, time starts from 01 chronologically so subtracting is uneeded)
			{
				time1 -= 12 * 60; // subtract 12 hours worth of minutes to account for it being the earliest am hour
			}
			if (c2.getSTime().substr(0, 2) == "12" && c2.getSTime().substr(5, 2) == "AM")// //If course 2's time is AM  and the hour is 12 (if it is not 12, time starts from 01 chronologically so subtracting is uneeded)
			{
				time2 -= 12 * 60; // subtract 12 hours worth of minutes to account for it being the earliest am hour
			}
			return time1 > time2; //return if course 1s time is later than course 2s time
		}
		else //Days are not the same
		{
			vector<string>days = { "Monday", "Tuesday", "Wednesday","Thursday","Friday" };//Initialize vector of all possible days
			int c1Day, c2Day;//Create 2 int variable to store indecies of the days
			for (int i = 0; i < (int)days.size(); i++)//Loop through all days
			{
				if (c1.getDay() == days[i])
				{
					c1Day = i;// If reached day in vector record index
				}
				else if (c2.getDay() == days[i])
				{
					c2Day = i; // If reached day in vector record index
				}
			}
			return c1Day < c2Day; //Return if first index is smaller than second (Indecies are in order of days of week) 
		}
	}
	else //If course numbers are different
	{
		return c1.getcourseNum() < c2.getcourseNum(); //Return if course 1s course number is less than course 2s course number
	}
}
bool customSort(const Course& c1, const Course& c2) //Sorting method if the user selected mode is custom
{
	if (c1.getDay() == c2.getDay()) //First order of rank (check if the days are the same)
	{
		if (c1.getSTime() == c2.getSTime()) // Second order of rank (check if the starting times are the same)
		{
			if (c1.getCourse() == c2.getCourse()) //Third order of rank (check if the name of the courses are the same)
			{
				return c1.getcourseNum() < c2.getcourseNum(); //Last order of rank (return if the courser number of course 1 is less than the course number of course 2)
			}
			else //if the course names are not the same
			{
				return c1.getCourse() < c2.getCourse(); //Return if course 1s name is alphabetically earlier than course 2s name
			}
		}
		else //If starting times are not the same
		{
			int time1 = leadTimeZero(c1.getSTime().substr(0, 2)) * 60 + leadTimeZero(c1.getSTime().substr(3, 2)); //Convert first time in terms of minutes (AM/PM dealt with later)
			int time2 = leadTimeZero(c2.getSTime().substr(0, 2)) * 60 + leadTimeZero(c2.getSTime().substr(3, 2));//Convert second time in terms of minutes (AM/PM dealt with later)
			if (c1.getSTime().substr(5, 2) == "PM" && c1.getSTime().substr(0, 2) != "12") //If course 1's time is PM and the hour is not 12 (if it is 12, pm is already acounted for by the hour being 12)
			{
				time1 += 12 * 60; //add 12 hours worth of minutes to account for it being pm
			}
			if (c2.getSTime().substr(5, 2) == "PM" && c2.getSTime().substr(0, 2) != "12") //If course 2's time is PM and the hour is not 12 (if it is 12, pm is already acounted for by the hour being 12)
			{
				time2 += 12 * 60; //add 12 hours worth of minutes to account for it being pm
			}
			if (c1.getSTime().substr(0, 2) == "12" && c1.getSTime().substr(5, 2) == "AM") // //If course 1's time is AM  and the hour is 12 (if it is not 12, time starts from 01 chronologically so subtracting is uneeded)
			{
				time1 -= 12 * 60; //Subtract 12 hours worth of minutes to account for it being the beggining of am
			}
			if (c2.getSTime().substr(0, 2) == "12" && c2.getSTime().substr(5, 2) == "AM")// //If course 2's time is AM  and the hour is 12 (if it is not 12, time starts from 01 chronologically so subtracting is uneeded)
			{
				time2 -= 12 * 60;//Subtract 12 hours worth of minutes to account for it being the beggining of am
			}
			return time1 < time2; //return if time1 is less than time 2
		}
	}
	else
	{
		vector<string>days = { "Monday", "Tuesday", "Wednesday","Thursday","Friday" };//Initialize vector of all possible days
		int c1Day, c2Day;//Create 2 int variable to store indecies of the days
		for (int i = 0; i < (int)days.size(); i++)//Loop through all days
		{
			if (c1.getDay() == days[i])
			{
				c1Day = i;// If reached day in vector record index
			}
			else if (c2.getDay() == days[i])
			{
				c2Day = i; // If reached day in vector record index
			}
		}
		return c1Day < c2Day; //Return if first index is smaller than second (Indecies are in order of days of week) 
	}
}
vector<string> split(string& str, const char del) //Helper method to split any string into a vector of strings based on a given character
{
	vector<string> splitStr;
	string temp = "";
	for (int i = 0; i < (int)str.size(); i++) //Loop through every character in given string
	{
		if (str[i] != del)
		{
			temp += str[i]; //If you haven't reached the split character keep adding character to temp string
		}
		else
		{
			splitStr.push_back(temp); //Once reached split key, push string to vector
			temp = ""; //Reset the temp string
		}
	}
	splitStr.push_back(temp); //to account for last argument because never hits another del key
	return splitStr; //Return vector of split strings
}

