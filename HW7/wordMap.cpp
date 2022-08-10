#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <vector>
#include <map>
#include <cctype>
#include <cassert>
#include <ctime>
#include "wordMap.h"
using namespace std;
typedef  map<string, map<string, map<string, int>>>  MY_MAP;

//Initialize wordMap object to store the words and window size
wordMap::wordMap(MY_MAP&data,int window)
{
	this->data = data;
    this->window = window;
    seed = true;
}

//Helper method to split a phrase into a pair of strings
pair<string, string> wordMap::split(string str)
{
    pair<string, string> splitStr;
    string str1 = "";
    string str2 = "";
    bool spacePased = false;
    //Loop thru each char in str
    for (int i = 0; i < (int)str.size(); i++)
    {
        //Keep going until reach empty char
        if (!spacePased && str[i] != ' ')
        {
            str1 += str[i];
        }
        //if ' ' reached, set first word and set as passed
        else if (str[i] == ' ')
        {
            splitStr.first = str1;
            spacePased = !spacePased;
        }
        //Add string 2
        else
        {
            str2 += str[i];
        }
    }
    splitStr.first = str1;
    splitStr.second = str2;
    //If str has no spaces, second string will reamin ""
    return splitStr;
}

//Method to set a seperate data map for the final 1 or 2 words in txt depending on window size
void wordMap::updateFinData(MY_MAP finData)
{
    this->finData = finData;
}

//Helper method that returns the next most common word for window = 2
string wordMap::findMax(map<string, int>& inData)
{
    int max = 0;
    string str;
    map<string, int>::iterator it = inData.begin();
    //Iterate through each possible word
    while (it != inData.end())
    {
        //Check count of each possible word and set max
        if (it->second > max)
        {
            max = it->second;
            str = it->first;
        }
        it++;
    }
    return str;
}

//Helper method that returns the next most common word for window = 3
string wordMap::findMax(map <string, map<string, int>>& inData)
{
    int max = 0;
    string str;
    map <string, map<string, int>>::iterator it = inData.begin();
    //Iteratre through each possible word
    while (it != inData.end())
    {
        int count = 0;
        //Iterate through inner map of map<string,int>
        for (map<string, int>::iterator i = it->second.begin(); i != it->second.end(); i++)
        {
            //keep total count
            count += i->second;
        }
        //If count is > than cur max set it as the max string
        if (count > max)
        {
            str = it->first;
        }
        it++;
    }
    return str;
}

//Helper method that sets the percentages for the next possible words for window = 2
void wordMap::findPercentage(map <string, int>& inData)
{
    double count = 0;
    map <string, int>::iterator it = inData.begin();
    //Loop through inner data to get a count of all occurances
    while (it != inData.end())
    {
        count += it->second;
        it++;
    }
    it = inData.begin();
    while (it != inData.end())
    {
        //Divide occurances by total words for percentage
        percentage[it->first] = ((double)it->second) / count;
        it++;
    }

}

//Helper method that sets the percentages for the next possible words for window = 3
void wordMap::findPercentage(map <string, map<string, int>>& inData, pair<string, string> words)
{
    double count= 0.0;
    map <string, map<string, int>>::iterator it = inData.begin();
    while (it != inData.end())
    {
        for (map<string, int>::iterator i = it->second.begin(); i != it->second.end(); i++)
        {
            // given only 1 word, need to find the total of all for the first word
            if (words.second == "") 
            {
                count += (double)i->second;
            }
            else
            {
                // if found the right second word (given 2 words)
                if (inData.find(words.second) == it) 
                {
                    count += (double)i->second;
                }

            }
        }
        it++;
    }

    
    it = inData.begin(); //reset it to beggining
    while (it != inData.end())
    {
        //Loop through same words, and set percentages of each potential word
        for (map<string, int>::iterator i = it->second.begin(); i != it->second.end(); i++)
        {
            if (words.second == "")
            {
                percentage[it->first] += (double)i->second / count; //given 1 word
            }
            else
            {
                if (inData.find(words.second) == it)
                {
                    percentage[i->first] = (double)i->second / count;//given 2 words
                }

            }
        }
        it++;
    }
}

//Helper method to parse thru and pass according map to findMax method and return the next most common word
string wordMap::NextWordMax(pair<string, string> words)
{
    string str;
    //Choose correct overloaded method if window size is 2
    if (window == 2)
    {
        //parse data and pass to findMax()
        map<string, map<string, int>>::iterator it = data.begin()->second.find(words.first);
        if (it != data.begin()->second.end())
        {
            str = findMax(it->second);
        }
    }
    //Choose correct overloaded method if window size is 3
    else
    {
        MY_MAP::iterator it = data.find(words.first);
        //only given 1 word
        if (words.second == "" && it != data.end())
        {
            str = findMax(it->second);
        }
        //given 2 words
        else if (it != data.end())
        {
            str = findMax((it->second).find(words.second)->second);
        }
        else
        {
            cout << "error";
        }
    }
    return str;
}

//Helper method to parse thru and pass according map to findPercentage method and return the next random word
string wordMap::NextWordRand(pair<string, string> words)
{
    //Only want to set srand() once to randomize
    if (seed)
    {
        srand(time(NULL));
        seed = false;
    }

    //Get randome number (0.0-1.0)
    double randVal = (double)rand() / RAND_MAX;
    double total = 0.0;
    string str = "";
    if (window == 2) //2
    {
        findPercentage(data.begin()->second.find(words.first)->second);
    }
    else //3
    {
        MY_MAP::iterator it = data.find(words.first);
        if (it != data.end()) // only 1 word
        {
            findPercentage(it->second, words);
        }
        else
        {
            cerr << "ERROR LINE 365";
        }
    }
    //Loop thru all potential percentages for words
    for (map<string, double>::iterator itr = percentage.begin(); itr!=percentage.end(); itr++)
    {
        //Keep a running total of percentages 
        //if the total is ever greater than random percentage, found chosen word
        total += itr->second;
        if (randVal < total)
        {
            str = itr->first;
            return str; 
        }
    }
    return str;
}

//Method to put together entire string based on user input
const string wordMap::generate(string phrase, int length, bool mode)
{
    string str = phrase;
    pair<string, string> words = split(phrase);
    string tempstr;
    //Loop thru number of words designated by user
    for (int i = 0; i < length; i++)
    {
        str += " ";
        if (mode) //mode true means most common, false means random
        {
            tempstr = NextWordMax(words);
        }
        else
        {
            tempstr = NextWordRand(words);
        }

        str += tempstr;
        if (window == 3) //window = 3
        {
            //Check if given 1 or 2 words
            if (words.second == "")
            {
                words.second = tempstr;
            }
            else
            {
                //keep pair of strings always the last 2 strings of the additive phrase
                words.first = words.second;
                words.second = tempstr;
            }
        }
        else //window = 2
        {
            words.first = tempstr;
        }
        percentage.clear();
    }
    return str;

}

//Method to print out occurances of given phrase as well as occurances of a possible next word
const vector<string> wordMap::print(string phrase)
{
    vector<string> finPrint;
    pair<string, string> words = split(phrase);

    //Window = 2
    if (window == 2)
    {
        int count = 0;
        //Ensure the word is in the map
        if (data.begin()->second.find(words.first) != data.begin()->second.end())
        {
            map<string, int>::iterator it = data.begin()->second.find(words.first)->second.begin();
            //Loop through all inner strings of the first word
            for (; it != data.begin()->second.find(words.first)->second.end(); it++)
            {
                //Keep running sum of ints
                string str = phrase;
                count += it->second;
                //Push back 2 word string
                str += " " + it->first + " (" + to_string(it->second) + ")";
                finPrint.push_back(str);
            }
            //Check the last words
            if (finData.begin()->second.begin()->first == phrase)
            {
                count++;
            }
            string totalstr = phrase + " (" + to_string(count) + ")";

            //Insert occurances of given phrase at first spot of vector
            finPrint.insert(finPrint.begin(), totalstr);
        }
        else
        {
            finPrint.push_back(words.first + " (0)");
        }       
    }

    //Window = 3 but given 1 word
    else if (words.second == "")
    {
        string str = phrase;
        int count = 0;
        MY_MAP::iterator it = data.find(words.first);
        if (it != data.end())
        {
            //Loop through map corresponding to given first word
            for (map<string, map<string, int>>::iterator it2 = it->second.begin(); it2 != it->second.end(); it2++)
            {
               int counttemp = 0;   
               string str = phrase;
               //Loop through each inner words map
                for (map<string, int>::iterator it3 = it2->second.begin(); it3 != it2->second.end(); it3++)
                {
                    count += it3->second;
                    counttemp += it3->second;
                }
                //Check map of last words(inner)
                for (MY_MAP::iterator itr = finData.begin(); itr != finData.end(); itr++)
                {
                    if (itr->first == phrase && itr->second.begin()->first == it2->first)
                    {
                        counttemp += itr->second.begin()->second.begin()->second;
                    }
                }
                str += " " + it2->first + " (" + to_string(counttemp) + ")";
                finPrint.push_back(str);

            }
            //Check map of last words
            for (MY_MAP::iterator itr = finData.begin(); itr != finData.end(); itr++)
            {
                string str = itr->first;
                if (str == phrase)
                {
                    count+=itr->second.begin()->second.begin()->second;
                }
            }
            string firstStr = phrase + " (" + to_string(count) + ")";

            //Insert occurances of given phrase at first spot of vector
            finPrint.insert(finPrint.begin(), firstStr);
        }
        else
        {
            finPrint.push_back(words.first + " (0)");
        }
    }

    //Window = 3 but given 2 words
    else
    {
        int count = 0;
        //Iterator of inner most map corresponding to first and second words
        map<string,int>::iterator it = data.find(words.first)->second.find(words.second)->second.begin();
        if (it != data.find(words.first)->second.find(words.second)->second.end())
        {
            while (it != data.find(words.first)->second.find(words.second)->second.end())
            {
                //Push back 3 word phrase with according count
                string str = phrase + " " + it->first + " (" + to_string(it->second) + ")";
                finPrint.push_back(str);
                count += it->second;
                it++;
            }
            //Check map of last words
            for (MY_MAP::iterator itr = finData.begin(); itr != finData.end(); itr++)
            {
                string str = itr->first + " " + itr->second.begin()->first;
                if (str == phrase)
                {
                    count += itr->second.begin()->second.begin()->second;
                }
            }
            string firstStr = phrase + " (" + to_string(count) + ")";

            //Insert occurances of given phrase at first spot of vector
            finPrint.insert(finPrint.begin(), firstStr);
        }
        else
        {
            finPrint.push_back(words.first + " " + words.second + " (0)");
        }
       
    }
    return finPrint;

}