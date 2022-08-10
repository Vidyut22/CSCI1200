// -----------------------------------------------------------------
// HOMEWORK 7 WORD FREQUENCY MAPS
//
// You may use all of, some of, or none of the provided code below.
// You may edit it as you like (provided you follow the homework
// instructions).
// -----------------------------------------------------------------

#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <vector>
#include <map>
#include <cctype>
#include <cassert>
#include "wordMap.h"
using namespace std;

// ASSIGNMENT: FILL IN YOUR OWN MAP STRUCTURE
typedef  map<string, map<string, map<string, int>>>  MY_MAP;



// Custom helper function that reads the input stream looking for
// double quotes (a special case delimiter needed below), and white
// space.  Contiguous blocks of alphabetic characters are lowercased &
// packed into the word.
bool ReadNextWord(std::istream& istr, std::string& word) {
    char c;
    word.clear();
    while (istr) {
        // just "peek" at the next character in the stream
        c = istr.peek();
        if (isspace(c)) {
            // skip whitespace before a word starts
            istr.get(c);
            if (word != "") {
                // break words at whitespace
                return true;
            }
        }
        else if (c == '"') {
            // double quotes are a delimiter and a special "word"
            if (word == "") {
                istr.get(c);
                word.push_back(c);
            }
            return true;
        }
        else if (isalpha(c)) {
            // this a an alphabetic word character
            istr.get(c);
            word.push_back(tolower(c));
        }
        else {
            // ignore this character (probably punctuation)
            istr.get(c);
        }
    }
    return false;
}


// Custom helper function that reads the input stream looking a
// sequence of words inside a pair of double quotes.  The words are
// separated by white space, but the double quotes might not have
// space between them and the neighboring word.  Punctuation is
// ignored and words are lowercased.
std::vector<std::string> ReadQuotedWords(std::istream& istr) {
    // returns a vector of strings of the different words
    std::vector<std::string> answer;
    std::string word;
    bool open_quote = false;
    while (ReadNextWord(istr, word)) {
        if (word == "\"") {
            if (open_quote == false) { open_quote = true; }
            else { break; }
        }
        else {
            // add each word to the vector
            answer.push_back(word);
        }
    }
    return answer;
}

// Loads the sample text from the file, storing it in the map data
// structure Window specifies the width of the context (>= 2) of the
// sequencing stored in the map.  parse_method is a placeholder for
// optional extra credit extensions that use punctuation.
void LoadSampleText(MY_MAP& data, const std::string& filename, int window, const std::string& parse_method, MY_MAP& finData)
{
    // open the file stream
    std::ifstream istr(filename.c_str());
    if (!istr) {
        std::cerr << "ERROR cannot open file: " << filename << std::endl;
        exit(1);
    }
    // verify the window parameter is appropriate
    if (window < 2) {
        std::cerr << "ERROR window size must be >= 2:" << window << std::endl;
    }
    // verify that the parse method is appropriate
    bool ignore_punctuation = false;
    if (parse_method == "ignore_punctuation") {
        ignore_punctuation = true;
    }
    else {
        std::cerr << "ERROR unknown parse method: " << parse_method << std::endl;
        exit(1);
    }
    assert(ignore_punctuation);
    string word;
    string tempstr1;
    string tempstr2;
    string finWord;
    int count = 0;
    while (ReadNextWord(istr, word)) 
    {
        // skip the quotation marks (not used for this part)
        if (word == "\"") continue;

        if (window == 2)
        {
            //Only start setting map on 2nd iteration to have 2 words
            if (count != 0)
            {
                //Still store words of window = 2 in a MY_MAP,although first string is always 2
                data["2"][tempstr1][word]++;
            }
            else
            {
                count = 1;
            }
            tempstr1 = word;
            tempstr2 = "2";
            

        }
        else if (window == 3)
        {
            //Only start setting map on 3rd iteration to have all 3 words
            if (count > 1)
            {
                data[tempstr2][tempstr1][word]++;
            }
            if (count > 0)
            {
                tempstr2 = tempstr1;
            }
            tempstr1 = word;
            count++;
        }
        else
        {
            std::cerr << "INVALID WINDOW INPUT" << parse_method << std::endl;
            exit(1);
        }
    }
    //Set last word
    finData[tempstr2][tempstr1][""]++;
    //If window = 3 set second to last word
    if (window == 3)
    {
        finData[tempstr1][""][""]++;
    }
}

int main()
{
    // ASSIGNMENT: THE MAIN DATA STRUCTURE
    MY_MAP data;
    wordMap wordData = wordMap(data, 0);
    // Parse each command
    std::string command;
    while (std::cin >> command)
    {

        // load the sample text file   
        if (command == "load")
        {
            std::string filename;
            int window;
            std::string parse_method;
            std::cin >> filename >> window >> parse_method;
            MY_MAP finData;

            //Loap map
            LoadSampleText(data, filename, window, parse_method,finData);
            //Initialize wordMap object
            wordData = wordMap(data, window); 
            //Set final data
            wordData.updateFinData(finData);

            cout << "Loaded " << filename << " with window = " << window << " and parse method = " << parse_method << "\n" << endl;
        }

        // print the portion of the map structure with the choices for the
        // next word given a particular sequence.
        else if (command == "print")
        {
            std::vector<std::string> sentence = ReadQuotedWords(std::cin);
            string phrase = "";
            //Turn vector of strings into single string
            for (int i = 0; i < (int)sentence.size(); i++)
            {
                if (i != 0)
                {
                    phrase += " ";
                }
                phrase += sentence[i];
            }
            //Call to print() method
            vector<string> finPrint = wordData.print(phrase);

            //Print out all strings from print() method
            for (int i = 0; i < (int)finPrint.size(); i++)
            {
                cout << finPrint[i] << endl;
            }
            cout << endl;
        }

        // generate the specified number of words 
        else if (command == "generate")
        {
            std::vector<std::string> sentence = ReadQuotedWords(std::cin);
            // how many additional words to generate
            int length;
            std::cin >> length;
            std::string selection_method;
            std::cin >> selection_method;
            bool random_flag;
            if (selection_method == "random")
            {
                random_flag = false;
            }
            else
            {
                assert(selection_method == "most_common");
                random_flag = true;
            }
            string phrase = "";
            //Turn vector of strings into single string
            for (int i = 0; i < (int)sentence.size(); i++)
            {
                if (i != 0)
                {
                    phrase += " ";
                }
                phrase += sentence[i];
            }
            //Call to generate() method (pass in which kind of generate)
            string result = wordData.generate(phrase, length, random_flag);
            cout << result << endl;

        }
        else if (command == "quit")
        {
            break;
        }
        else
        {
            std::cout << "WARNING: Unknown command: " << command << std::endl;
        }
    }
    return 0;
}
