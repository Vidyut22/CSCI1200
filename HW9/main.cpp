#include <iostream>
#include <fstream>
#include <string>
#include <utility>
#include <cassert>
#include <vector>
#include <algorithm>
#include <map>
#include <unordered_map>
#include "Map.h"
using namespace std;

/*
Helper method to split a string into a vector of
string based on each ' ' character
*/
vector<string> split(string s)
{
    vector<string> tmp;
    string str = "";

    //Loop thru all characters is larger string
    for (unsigned int i = 0; i < s.size(); i++)
    {
        if (s[i] == ' ')
        {
            //Add string to vector
            tmp.push_back(str);
            str.clear();
        }
        else
        {
            str += s[i];
        }
    }
    //Add last string
    tmp.push_back(str);
    return tmp;
}
// Keep looping cin until given quit command
int main(int argc, char* argv[])
{  
    map<string, string> actorMap;
    HashMap map;
    string command;
    while (getline(cin, command))
    {
        //Create vecotor of strings for each line given
        vector<string> commandVec = split(command);
        if (commandVec[0] == "table_size")
        {
            map.setSize(stoi(commandVec[1]));
        }
        else if (commandVec[0] == "occupancy")
        {
            map.setOccupancy(stof(commandVec[1]));
        }
        else if (commandVec[0] == "movies")
        {
            ifstream movieFile(commandVec[1]);
            string category = "";
            int count = 0;
            Movie m;
            //Loop thru movie file and create a movie
            //for each movie in file
            while (getline(movieFile, category))
            { 
                //If position is 6 means read all categories for movie
                if (count == 6)
                {
                    //Populate table then
                    count = 0;
                    map.populateTable(m);
                    m.clear();
                }
                if (count == 0)
                {
                    m.setTitle(category);
                }
                else if (count == 1)
                {
                    m.setYear(category);
                }
                else if (count == 2)
                {
                    m.setRunTime(category);
                }
                else if (count == 3)
                {
                    vector<string> tmp = split(category);
                    if (tmp[0] != "0")
                    {
                        //Dont need size anymore
                        tmp.erase(tmp.begin());
                        m.setGenres(tmp);
                    }
                }
                else if (count == 4)
                {
                    vector<string> tmp = split(category);
                    if (tmp[0] != "0")
                    {
                        //Dont need size anymore
                        tmp.erase(tmp.begin());
                        m.setActors(tmp);
                    }
                }
                else if (count == 5)
                {
                    vector<string> tmp = split(category);
                    if (tmp[0] != "0")
                    {
                        //Dont need size anymore
                        tmp.erase(tmp.begin());
                        m.setRoles(tmp);
                    }
                }
                count++;

            }
            //For the last movie
            map.populateTable(m); 
        }
        else if (commandVec[0] == "actors")
        {
            ifstream file(commandVec[1]);
            string str;
            while (getline(file,str))
            {
                vector<string> actorVec = split(str);
                actorMap.insert(pair<string, string>(actorVec[0], actorVec[1]));
            }
            map.setActorMap(actorMap);
        }
        else if (commandVec[0] == "query")
        {
            Query q;
            //Loop for all categories in Query and set all of them
            for (int i = 0; i < 6; i++)
            {
                getline(cin, command);
                if (i == 0)
                {
                    q.setTitle(command);
                }
                else if (i == 1)
                {
                    q.setYear(command);
                }
                else if (i == 2)
                {
                    q.setRunTime(command);
                }
                else if (i == 3)
                {
                    vector<string> tmp = split(command);
                    if (tmp[0] != "0")
                    {
                        //Dont need size anymore
                        tmp.erase(tmp.begin());
                        q.setGenres(tmp);
                    }
                }
                else if (i == 4)
                {
                    vector<string> tmp = split(command);
                    if (tmp[0] != "0")
                    {
                        //Dont need size anymore
                        tmp.erase(tmp.begin());
                        q.setActors(tmp);
                    }
                }
                else if (i == 5)
                {
                    vector<string> tmp = split(command);
                    if (tmp[0] != "0")
                    {
                        //Dont need size anymore
                        tmp.erase(tmp.begin());
                        q.setRoles(tmp);
                    }
                }
            }
            //Once made the query search for is in map
            pair<bool, tableRep::iterator> foundQuery = map.find(q);
            map.print(foundQuery);
        }
        //QUIT PROGRAM
        else if (commandVec[0] == "quit") 
        {
            break;
        }
    }
    return argc;
}