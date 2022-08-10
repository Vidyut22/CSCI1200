#include "Course.h" //Include Course class
#include <iostream>
#include <fstream>
#include <cassert>
#include <vector>
#include <string>
#include <iomanip>
#include <cmath>
#include <cstdlib>
#include <algorithm>
using namespace std;
bool firstRoom = true; //Used in output to ensure output file only opens once (on the first loop)

vector<Course> readFile(const string& font_file) //Method to read and parse info from input file
{
	vector<Course>courses; //Initialize empty vector to hold multople course objects
	ifstream file(font_file);
	string str;
	while (getline(file, str)) //Get each line in input file
	{
		vector<string>courseInfo = split(str, ' '); //Call split helper method to split each line into individual data of a snigle course

		//Loop through vector as many times as characters in 5th argument (Days) to create multiple courses for courses of multiple days
		for (int i = 0; i < (int)courseInfo[4].size(); i++)
		{
			courses.push_back(Course(stoi(courseInfo[0]),//Convert first index to int (crn number)
				courseInfo[1], //Department
				courseInfo[2], //Course Number
				courseInfo[3], // Course Name
				courseInfo[4][i], //Pass each day as character
				courseInfo[5], // Starting Time
				courseInfo[6], // End Time
				courseInfo[7])); // Room Name
		}
	}
	return courses; //Return vector of course objects filled with all input file data
}
int maxLeninSec(vector<Course>roomCourse, const string& mode) //Helper method to measure the max width of a given column in the table
{
	int max = 0; //Initialize max width which will be initially set to the length of each column title
	if (mode == "dept") //Determine if coloumn is for department
	{
		max = 4; //Dept = 4 characters
		for (int i = 0; i < (int)roomCourse.size(); i++) //Loop through all courses
		{
			if ((int)roomCourse[i].getDep().size() > max) //Check length of current courses department
			{
				max = roomCourse[i].getDep().size(); //If a courses department length is larger than max width, set that length to new max width
			}
		}
	}
	else if (mode == "coursenum") //Determine if coloumn is for course number
	{
		max = 9; //Coursenum = 9 characters
		for (int i = 0; i < (int)roomCourse.size(); i++) //Loop through all courses
		{
			if ((int)roomCourse[i].getcourseNum().size() > max) //Check length of current courses course number
			{
				max = roomCourse[i].getcourseNum().size(); //If a courses course number length is larger than max width, set that length to new max width
			}
		}
	}
	else if (mode == "classtitle") //Determine if coloumn is for class title/name
	{
		max = 11; //Class Title = 11 characters 
		for (int i = 0; i < (int)roomCourse.size(); i++) //Loop through all courses
		{
			if ((int)roomCourse[i].getCourse().size() > max) //Check length of current courses name
			{
				max = roomCourse[i].getCourse().size(); //If a courses class title length is larger than max width, set that length to new max width
			}
		}
	}
	else if (mode == "day")//Determine if coloumn is for day
	{
		max = 3; //Day = 3 characters
		for (int i = 0; i < (int)roomCourse.size(); i++) //Loop through all courses
		{
			if ((int)roomCourse[i].getDay().size() > max) //Check length of current courses day
			{
				max = roomCourse[i].getDay().size(); //If a courses day length is larger than max width, set that length to new max width
			}
		}
	}
	else if (mode == "starttime") //Determine if coloumn is for the start time
	{
		max = 10;  //Start Time = 10 characters
		for (int i = 0; i < (int)roomCourse.size(); i++) //Loop through all courses
		{
			if ((int)roomCourse[i].getSTime().size() > max) //Check length of current courses start time (for start time it should always be the same but incase of unkown outlier I included it)
			{
				max = roomCourse[i].getSTime().size(); //If a courses start time length is larger than max width, set that length to new max width
			}
		}
	}
	else if (mode == "endtime") //Determine if coloumn is for the end time
	{
		max = 8; //End Time = 8 characters
		for (int i = 0; i < (int)roomCourse.size(); i++) // Loop through all courses
		{
			if ((int)roomCourse[i].getETime().size() > max) //Check length of current courses end time (for end time it should always be the same but incase of unkown outlier I included it)
			{
				max = roomCourse[i].getETime().size(); //If a courses end time length is larger than max width, set that length to new max width
			}
		}
	}
	return max+2; //Account for 2 spaces in between coloumn (will take care of last coloumn spacing later)
}
void outputRoomData(vector<Course>courses, const string& outFile, string RoomDep, string& mode) //Overloaded method used for single table output
{
	if (firstRoom) //Check if its the first time in the method, to only open output file once (If it opens multiple times, it would reset the file each time)
	{
		ofstream myfile(outFile); // Only open output file once
	}
	ofstream myfile(outFile, ios::app);
	vector<Course>roomCourse; //Initialize empty vector to hold all rooms/departments/days of each course depending on mode
	if (mode == "room") // If mode equal to room
	{
		for (int i = 0; i < (int)courses.size(); i++) //Loop through all courses
		{
			if (courses[i].getRoom() == RoomDep) //Check if room of current course is equal to the given/desired room
			{
				roomCourse.push_back(courses[i]); //pushback all courses if their room is equal to given room
			}
			else if (roomCourse.size() != 0) //After all the desired rooms that are stacked up have ended, break out of loop because we know we have atained all rooms (courses has already been sorted)
			{
				break; //Break out of loop
			}
		}
	}
	else if(mode == "dept") //if mode equal to department
	{
		for (int i = 0; i < (int)courses.size(); i++) //Loop through all courses
		{
			if (courses[i].getDep() == RoomDep)//Check if department of current course is equal to the given/desired department
			{
				roomCourse.push_back(courses[i]); //pushback all courses if their department is equal to given department
			}
		}
	}
	else //mode == custom
	{
		for (int i = 0; i < (int)courses.size(); i++) //Loop through all courses
		{
			if (courses[i].getDay() == RoomDep)///Check if day of current course is equal to the given/desired day
			{
				roomCourse.push_back(courses[i]); //pushback all courses if their day is equal to given day
			}
			else if (roomCourse.size() != 0) //After all the desired day that are stacked up have ended, break out of loop because we know we have atained all days (courses has already been sorted)
			{
				break; //Break out of loop
			}
		}
	}

	
	if (myfile.is_open())
	{
		if ((int)roomCourse.size() != 0) //Ensure data available
		{
			//Get and store max length of each column (using helper method); Used when setting width of each column
			int dept = maxLeninSec(roomCourse, "dept");
			int coursenum = maxLeninSec(roomCourse, "coursenum");
			int classtitle = maxLeninSec(roomCourse, "classtitle");
			int day = maxLeninSec(roomCourse, "day");
			int starttime = maxLeninSec(roomCourse, "starttime");
			int endtime = maxLeninSec(roomCourse, "endtime");
			//Format all headers for all output situations
			if (mode == "room")
			{
				myfile << "Room " << RoomDep << endl; //Set room header along with room name
			}
			else if(mode == "dept")
			{
				myfile << "Dept " << RoomDep << endl; //Set Dept header along with department name
			}
			else
			{
				myfile << "Day " << RoomDep << endl; //Set Day header along with day name (custom mode)
			}
			if (mode != "dept") //Only need department column if mode is room or custom
			{
				myfile << setfill(' ') << setw(dept) << left << "Dept"; //Set spaces after header
			}
			myfile << setfill(' ') << setw(coursenum) << left << "Coursenum"; //Set spaces after header
			myfile << setfill(' ') << setw(classtitle) << left << "Class Title"; //Set spaces after header
			if (mode != "custom") //Only need Day column if mode is dept or room
			{
				myfile << setfill(' ') << setw(day) << left << "Day"; //Set spaces after header
			}
			myfile << setfill(' ') << setw(starttime) << left << "Start Time"; //Set spaces after header
			myfile << setfill(' ') << setw(endtime-2) << left << "End Time"<<endl; //Set spaces after header (Don't need extra 2 spaces for last column)
			if (mode != "dept")//Only need department column if mode is room or custom
			{
				myfile << setfill('-') << setw(dept) << right << "  ";//Setting column '-'
			}
			myfile << setfill('-') << setw(coursenum) << right << "  "; //Setting column '-'
			myfile << setfill('-') << setw(classtitle) << right << "  ";//Setting column '-'
			if (mode != "custom")//Only need Day column if mode is dept or room
			{
				myfile << setfill('-') << setw(day) << right << "  ";//Setting column '-'
			}
			myfile << setfill('-') << setw(starttime) << right << "  ";//Setting column '-'
			myfile << setfill('-') << setw(endtime-2) << right << ""<<endl; ////Setting column '-' (Don't need extra 2 spaces for last column)
			//Format all data  for all output situations
			for (int i = 0; i < (int)roomCourse.size(); i++) //Loop through all courses to get necessary data
			{
				if (mode != "dept") //department used for both room and custom situations
				{
					myfile << setfill(' ') << setw(dept) << left << roomCourse[i].getDep(); //Display actual department number for current course
				}
				myfile << setfill(' ') << setw(coursenum) << left << roomCourse[i].getcourseNum(); //Display actual course number for current course
				myfile << setfill(' ') << setw(classtitle) << left << roomCourse[i].getCourse(); //Display actual class name for current course
				if (mode != "custom") //day used for both room and department situations
				{
					myfile << setfill(' ') << setw(day) << left << roomCourse[i].getDay(); //Display actual room for current course
				}
				myfile << setfill(' ') << setw(starttime) << left << roomCourse[i].getSTime(); //Display actual start time for current course
				myfile << setfill(' ') << setw(endtime-2) << left << roomCourse[i].getETime() << endl; // Display endtime for current course (Don't need extra 2 spaces for last column)
			}
			myfile << (int)roomCourse.size() << " entries" << endl; //# of entries in table = length of course vector
			myfile << "\n"; // 2 spaces between each table
		}
		else //If no courses available
		{
			myfile << "No data available." << endl;
		}
	}
	firstRoom = false; //In order to not reopen output file, which would reset output file
}

void outputRoomData(vector<Course>courses, const string& outfile, string &mode) //Overloaded method used for multiple table output
{
	if (courses.size() != 0)
	{
		//No situation for department as it will default to overloaded outputRoomData method with an additional department argument
		if (mode == "room") //if mode = room
		{
			string temproom = ""; //Initialize empty temp string to add to
			for (int i = 0; i < (int)courses.size(); i++) //Loop through all courses
			{
				if (temproom != courses[i].getRoom() || i == 0) //Only output table once for each room (checks if room has been outputed before or it's the first room)
				{
					outputRoomData(courses, outfile, courses[i].getRoom(), mode); //Output each room table using single table output (overloaded "outputRoomData" from above)
					temproom = courses[i].getRoom(); //Set temporary string to the current room so that we will not call overloaded method again

				}
			}
		}
		else // if mode = custom
		{
			string tempDay = "";  //Initialize empty temp string to add to
			for (int i = 0; i < (int)courses.size(); i++) //Loop through all courses
			{
				if (tempDay != courses[i].getDay() || i == 0) //Only output table once for each day (checks if day has been outputed before or it's the first day)
				{
					outputRoomData(courses, outfile, courses[i].getDay(), mode); //Output each custom (day) table using single table output (overloaded "outputRoomData" from above)
					tempDay = courses[i].getDay(); //Set temporary string to the current day so that we will not call overloaded method again

				}
			}
		}
		
	}	
	else
	{
		outputRoomData(courses, outfile, "null" ,mode); //If the size of input vector is 0, simply pass vector to overloaded method (will take care of empty input)
	}
	
}


int main(int argc, char* argv[])
{
	vector<Course>inputdata = readFile(string(argv[1])); //Initialize input vector of all courses data from given txt file (unsorted)
	string mode = string(argv[3]); //room/dept/custom
	if (mode == "room")
	{
		sort(inputdata.begin(), inputdata.end(), roomSort); //Sort input vector according to room sorting algorithm
		if (argc == 4) //No room attached (needs to output all rooms data)
		{
			outputRoomData(inputdata, argv[2], mode); //Call overloaded method outputRoomData with 3 arguments
		}
		else if (argc == 5) //Room attached (neeeds to output 1 rooms data)
		{
			outputRoomData(inputdata, argv[2], argv[4],mode); //Call overloaded method outputRoomData with 4 arguments
		}
		else
		{
			cerr << "Incorrect number of arguments"<<endl; //error
		}
	}
	else if (mode == "dept")
	{
		sort(inputdata.begin(), inputdata.end(), depSort); //Sort input vector according to department sorting algorithm
		if (argc == 5) //Ensures correct number of arguments
		{
			outputRoomData(inputdata, argv[2], argv[4], mode); //Call overloaded method outputRoomData with 4 arguments
		}
		else
		{
			cerr << "Incorrect number of arguments" << endl; //error
		}
	}
	else if (mode == "custom")
	{
		sort(inputdata.begin(), inputdata.end(), customSort);//Sort input vector according to custom sorting algorithm
		if (argc == 4) //No day attached (needs to output all days data)
		{
			outputRoomData(inputdata, argv[2], mode); //Call overloaded method outputRoomData with 3 arguments
		}
		else if (argc == 5) //Day attached (neeeds to output 1 days data)
		{
			outputRoomData(inputdata, argv[2], argv[4], mode); //Call overloaded method outputRoomData with 4 arguments
		}
		else
		{
			cerr << "Incorrect number of arguments" << endl;//error
		}
	}
	else
	{
		cerr << "Mode not properley selected" << endl;//error
	}
}
