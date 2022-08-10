#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <vector>
#include <map>
#include <cctype>
using namespace std;
typedef  map<string, map<string, map<string, int>>>  MY_MAP;

class wordMap
{
public:
	//INITIALIZATION
	wordMap(MY_MAP &data,int window); 
	//ACTIONS
	const string generate(string phrase, int length, bool mode); //Generate full string
	const vector<string> print(string phrase); //Print out # of occurances
	//SETTERS
	void updateFinData(MY_MAP finData); //Set last words

private:
	//HELPER METHODS
	pair<string, string> split(string str); //split phrase into pair of strings
	string findMax(map<string, int>& inData); //find next common word
	string findMax(map <string, map<string, int>>& inData); 
	void findPercentage(map <string, int>& inData); //find percentages of possible words
	void findPercentage(map <string, map<string, int>>& inData, pair<string, string> words);
	string NextWordMax(pair<string, string> words); //parse data
	string NextWordRand(pair<string, string> words); // parse data
	//MEMBER VARIABLES
	int window; // Hold window size
	MY_MAP data; //Map to store words of given text
	map<string, double> percentage; // Map to hold percentages of potential words
	bool seed; // Used to only set srand() once
	MY_MAP finData; //Need to hold last 1 or 2 words (depending on window) seperatley to not affect rest of data
};
