#include <iostream>
#include <fstream>
#include <cassert>
#include <vector>
#include <string>
#include <iomanip>
#include <cmath>
#include <cstdlib>
#include "grid.h"
using namespace std;
int rows;
int cols;
bool mode = true;
vector<Zone>zones;
vector<vector<vector<string>>> gridStr;

//Helper method to split a string into 2 characters and return as a vector
vector<string> split(string str)
{
    vector<string> splitStr;
    string str1 = "";
    string str2 = "";
    bool spacePased = false;
    for (int i = 0; i < (int)str.size(); i++)
    {
        if (!spacePased && str[i]!= ' ')
        {
            str1 += str[i];
        }
        else if (str[i] == ' ')
        {
            splitStr.push_back(str1);
            spacePased = !spacePased;
        }
        else
        {
            str2 += str[i];
        }
    }
    splitStr.push_back(str2);
    return splitStr;
}

//Helper method to parse through input file and initialize useful global variables
void readFile(const string& inputFile)
{
    int count = 0;
    vector<string> curcoor;
    vector<vector<string>> coors;
    ifstream file(inputFile);
    string str;
    while (getline(file, str))
    {
        vector<string> nums; 
        nums = split(str);
        if (count == 0)
        {
            rows = stoi(nums[0]);
            cols = stoi(nums[1]);
            count++;
        }
        else if (int(nums[0][0]) > 57)
        {
            if (count != 1)
            {
                gridStr.push_back(coors);
            }
            count++;
            coors.clear();
            curcoor.push_back(nums[0]);
            curcoor.push_back(nums[1]);
            coors.push_back(curcoor);
            curcoor.clear();
            zones.push_back(Zone(nums[0][0]));
        }
        else
        {
            
            curcoor.push_back(nums[0]);
            curcoor.push_back(nums[1]);
            coors.push_back(curcoor);
            curcoor.clear();
        }
    }
    gridStr.push_back(coors);
}

//Print method for if user says print
void print(string outFile , Grid starBattle)
{
    ofstream myfile(outFile);
    if (myfile.is_open())
    {
        myfile << starBattle;
    }
}
//Print method for if user says count
void print(string outFile, int solutions)
{
    ofstream myfile(outFile);
    if (myfile.is_open())
    {
        myfile << "Number of solutions: " << solutions << endl;
    }
}

int main(int argc, char* argv[])
{
    int sVal = stoi(argv[3]);

    //Understand what user is asking for
    string outputMode = string(argv[4]);
    string modeType = string(argv[5]);
    assert(modeType == "all_solutions" || modeType == "one_solution");
    if (modeType == "one_solution")
    {
        mode = false;
    }

    //Parse thru input file
    readFile(string(argv[1]));

    //Create a grid called starBattle based on given vals
    Grid starBattle = Grid(sVal,rows, cols, zones, gridStr, mode);

    //Complete all solutions
    starBattle.completeSolution(0, 0, 0); 

    //Understand what user is asking for
    assert(outputMode == "count" || outputMode == "print");
    if (outputMode == "count")
    {
        print(argv[2], starBattle.getSolutionBoard().size());
    }
    else
    {
        print(argv[2],starBattle);
    }
    
    return argc;
}