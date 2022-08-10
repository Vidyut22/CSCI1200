#include <iostream>
#include <fstream>
#include <cassert>
#include <vector>
#include <string>
#include <iomanip>
#include <cmath>
#include <cstdlib>
using namespace std; //Using entire std library
vector<vector<char>> readFile(const string& font_file) // Method to retreive data from inputfile
{
    vector<vector<char>> Map; // Initialization of 2D vector for character storing
    ifstream file(font_file);
    string str;
    while (getline(file, str)) //Get each line from input file until end of data
    {
        vector<char> vec;
        for (int i = 0; i < (int)str.size(); i++) 
        {
            vec.push_back(str[i]); // add each character to a vector of one line in input file
        }
        Map.push_back(vec); // add each vector to another vector creating a 2D vector (Map) of characters
    }
    return Map;
}

void fileOut(vector<vector<char>> charMap, const string& outFile) //Method to output final data to a seperate output file
{
    ofstream myfile(outFile, ofstream::out); //Open file given a string name of file
    if (myfile.is_open())
    {
        for (int i = 0; i < (int)charMap.size(); i++) //Loop through every character in given map
        {
            for (int j = 0; j < (int)charMap[i].size(); j++)
            {
                myfile << charMap[i][j]; //Output each character to file
            }
            if (i != (int)charMap.size() - 1) // Go to next line as long as it is not the last line in the given map
            {
                myfile << "\n";
            }

        }
        myfile.close();
    }
    else
    {
        cerr << "Problem with opening output file"; //If it cannot open file display error message
    }
    
}

void print(vector<vector<char>>& charMap) // Helper method to print out any 2D vector of chars to terminal (used for testing purposes)
{
    for (int i = 0; i < (int)charMap.size(); i++) //Loop through every character in map
    {
        for (int j = 0; j < (int)charMap[i].size(); j++)
        {
            cout << charMap[i][j]; // Print each character to console
        }
        cout << "\n";
    }
}
vector<vector<char>> dilation(char find, vector<vector<char>> &Map) // (Returns a 2D map of dilated input) Method to complete the dilation feature given a starting character and a 2D map of the original input
{
    vector<vector<char>> diMap;// Create new 2D vector which will store the final eroded map
    for (int i = 0; i < (int)Map.size(); i++)// Create a 2D vector of same width and height of input map all with character '.'
    {
        vector<char> vec;
        for (int j = 0; j < (int)Map[i].size(); j++)
        {
            vec.push_back('.');
        }
        diMap.push_back(vec);

    }
    for (int i = 0; i < (int)Map.size(); i++)
    {
        for (int j = 0; j < (int)Map[i].size(); j++)
        {
            if (Map[i][j] != find)
            {
                if (i != 0 && i != (int)Map.size() - 1 && j != 0 && j != (int)Map[i].size() - 1) //Check if current character is not on the outside of the map
                {
                    if (Map[i - 1][j] == find || Map[i + 1][j] == find || Map[i][j - 1] == find || Map[i][j + 1] == find)  //Check if any surrounding character is equal to the given character
                    {
                        diMap[i][j] = find;
                    }
                    else
                    {
                        diMap[i][j] = Map[i][j];
                    }
                }
                //Go through every outside combonation and only check possible memorey locations given the input character location
                else if (i == 0)
                {
                    if (j == 0)
                    {
                        if (Map[i + 1][j] == find || Map[i][j + 1] == find)
                        {
                            diMap[i][j] = find;
                        }
                        else
                        {
                            diMap[i][j] = Map[i][j];
                        }
                    }
                    else if (j == (int)Map[i].size() - 1)
                    {
                        if (Map[i + 1][j] == find || Map[i][j - 1] == find)
                        {
                            diMap[i][j] = find;
                        }
                        else
                        {
                            diMap[i][j] = Map[i][j];
                        }
                    }
                    else
                    {
                        if (Map[i + 1][j] == find || Map[i][j - 1] == find || Map[i][j + 1] == find)
                        {
                            diMap[i][j] = find;
                        }
                        else
                        {
                            diMap[i][j] = Map[i][j];
                        }
                    }
                }
                else if (j == 0)
                {
                    if (i == (int)Map.size() - 1)
                    {
                        if (Map[i - 1][j] == find || Map[i][j + 1] == find)
                        {
                            diMap[i][j] = find;
                        }
                        else
                        {
                            diMap[i][j] = Map[i][j];
                        }
                    }
                    else
                    {
                        if (Map[i - 1][j] == find || Map[i + 1][j] == find || Map[i][j + 1] == find)
                        {
                            diMap[i][j] = find;
                        }
                        else
                        {
                            diMap[i][j] = Map[i][j];
                        }
                    }
                }
                else if (i == (int)Map.size() - 1)
                {
                    if (j == (int)Map[i].size() - 1)
                    {
                        if (Map[i][j - 1] == find || Map[i - 1][j] == find)
                        {
                            diMap[i][j] = find;
                        }
                        else
                        {
                            diMap[i][j] = Map[i][j];
                        }
                    }
                    else
                    {
                        if (Map[i - 1][j] == find || Map[i][j - 1] == find || Map[i][j + 1] == find)
                        {
                            diMap[i][j] = find;
                        }
                        else
                        {
                            diMap[i][j] = Map[i][j];
                        }
                    }
                }
                else
                {
                    if (Map[i + 1][j] == find || Map[i][j - 1] == find || Map[i - 1][j] == find)
                    {
                        diMap[i][j] = find;
                    }
                    else
                    {
                        diMap[i][j] = Map[i][j];
                    }
                }
            }
            else
            {
                diMap[i][j] = find;
            }
        }
    }
    return diMap;
}
vector<vector<char>> erosion(char find, char bg, vector<vector<char>> &Map) //Method to complete erosion feature
{
    vector<vector<char>> erMap; // Create new 2D vector which will store the final eroded map
    for (int i = 0; i < (int)Map.size(); i++) // Create a 2D vector of same width and height of input map all with character '.'
    {
        vector<char> vec;
        for (int j = 0; j < (int)Map[i].size(); j++)
        {
            vec.push_back('.');
        }
        erMap.push_back(vec);
        
    }
    for (int i = 0; i < (int)Map.size(); i++) //Loop through each character in input map 
    {
        for (int j = 0; j < (int)Map[i].size(); j++)
        {
            if (Map[i][j] == find)
            {
                if (i != 0 && i != (int)Map.size() - 1 && j != 0 && j != (int)Map[i].size() - 1) //Check if current character is not on the outside of the map
                {
                    if (Map[i - 1][j] == find && Map[i + 1][j] == find && Map[i][j - 1] == find && Map[i][j + 1] == find)
                    {
                        erMap[i][j] = find;
                    }
                    else
                    {
                        erMap[i][j] = bg;
                    }
                }
        //Go through every outside combonation and only check possible memorey locations given the input character location
                else if (i == 0)
                {
                    if (j == 0)
                    {
                        if (Map[i + 1][j] == find && Map[i][j + 1] == find)
                        {
                            erMap[i][j] = find;
                        }
                        else
                        {
                            erMap[i][j] = bg;
                        }
                    }
                    else if (j == (int)Map[i].size() - 1)
                    {
                        if (Map[i + 1][j] == find && Map[i][j - 1] == find)
                        {
                            erMap[i][j] = find;
                        }
                        else
                        {
                            erMap[i][j] = bg;
                        }
                    }
                    else
                    {
                        if (Map[i + 1][j] == find && Map[i][j - 1] == find && Map[i][j + 1] == find)
                        {
                            erMap[i][j] = find;
                        }
                        else
                        {
                            erMap[i][j] = bg;
                        }
                    }
                }
                else if(j == 0)
                {
                    if (i == (int)Map.size() - 1)
                    {
                        if (Map[i - 1][j] == find && Map[i][j + 1] == find)
                        {
                            erMap[i][j] = find;
                        }
                        else
                        {
                            erMap[i][j] = bg;
                        }
                    }
                    else
                    {
                        if (Map[i - 1][j] == find && Map[i+1][j] == find && Map[i][j + 1] == find)
                        {
                            erMap[i][j] = find;
                        }
                        else
                        {
                            erMap[i][j] = bg;
                        }
                    }
                }
                else if (i == (int)Map.size() - 1)
                {
                    if (j == (int)Map[i].size() - 1)
                    {
                        if (Map[i][j - 1] == find && Map[i-1][j] == find)
                        {
                            erMap[i][j] = find;
                        }
                        else
                        {
                            erMap[i][j] = bg;
                        }
                    }
                    else
                    {
                        if (Map[i - 1][j] == find && Map[i][j - 1] == find && Map[i][j + 1] == find)
                        {
                            erMap[i][j] = find;
                        }
                        else
                        {
                            erMap[i][j] = bg;
                        }
                    }
                }
                else
                {
                    if (Map[i + 1][j] == find && Map[i][j - 1] == find && Map[i - 1][j] == find) 
                    {
                        erMap[i][j] = find;
                    }
                    else
                    {
                        erMap[i][j] = bg;
                    }
                }
            }
            //If given character is not found, keep it as the background character
            else
            {
                erMap[i][j] = bg;
            }
        }
    }
    return erMap;
}
void replace(char find, char rep, vector<vector<char>> &Map) //Method to replace all given chars with a replacement character
{
    for (int i = 0; i < (int)Map.size(); i++) //Loop through every character in given Map
    {
        for (int j = 0; j < (int)Map[i].size(); j++)
        {
            if (Map[i][j] == find) //Replace current character with given character if they match
            {
                Map[i][j] = rep;
            }
        }
    }
}

int main(int argc, char *argv[]) 
{
    vector<vector<char>> charMap = readFile(argv[1]); //Reads input from inputfile and stores in 2D map of characters
    string mode = string(argv[3]); 
    if (mode == "replace") //Determine which mode to use (replace, erosion, dilation)
    {
        replace(argv[4][0], argv[5][0], charMap); //Modifies original map and replaces characters with given character
        print(charMap); //print replace map to terminal
        fileOut(charMap, string(argv[2])); // Outputs modified map to an output txt file
    }
    
    else if (mode == "erosion")
    {
        vector<vector<char>> erMap = erosion(argv[4][0], argv[5][0], charMap); // Creates new "eroded" map and stores it in 2D vector
        print(erMap); // print eroded map to terminal
        fileOut(erMap, string(argv[2])); // Outputs new map to an output txt file
    }
    else if (mode == "dilation")
    {
        vector<vector<char>> diMap = dilation(argv[4][0], charMap);// Creates new "dilated" map and stores it in 2D vector
        print(diMap);// print eroded map to terminal
        fileOut(diMap, string(argv[2]));// Outputs new map to an output txt file
    }
    return 0; //Return main method
    
}


