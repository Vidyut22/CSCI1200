#ifndef coursefile
#define coursefile

#include <string>
#include <vector>
using namespace std;
class Course //Create class named course
{
public:
	Course(int crn, string dep, string courseNum, string course, char day, string stime, string etime, string room); //Default constructor (requires all member variables)
	
	//Accessors
	int getCRN() const;
	string getDep() const;
	string getcourseNum() const;
	string getCourse() const;
	string getDay() const; //Accessor method will return a string even though private member variable is a char (implemented in .cpp)
	string getSTime() const;
	string getETime() const;
	string getRoom() const;

	//No modifiers necessary
private:
	//private memeber variables
	int crn;
	string dep;
	string courseNum;
	string course;
	char day;
	string stime;
	string etime;
	string room;
};
bool roomSort(const Course& c1, const Course& c2); //Sorting method if the user selected mode is room
bool depSort(const Course& c1, const Course& c2);//Sorting method if the user selected mode is dept
bool customSort(const Course& c1, const Course& c2);//Sorting method if the user selected mode is custom
vector<string> split(string& str, const char del); // Helper method to split up strings in input file into individual members of course object
int leadTimeZero(string& str); // helper method to deal with time

#endif