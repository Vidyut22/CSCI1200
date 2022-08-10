#include <cassert>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <string>
#include <set>
#include <map>
using namespace std;

// defined in performance.cpp
void usage();

template <class T>
void bst_sort(map<T,int> &s, ostream& ostr, int& output_count)
{
    output_count = 0;
    //loop all elements in map
    for (typename map<T,int>::iterator itr = s.begin(); itr!=s.end();itr++)
    {
        for (int i = 0; i < itr->second; i++)
        {
            ostr << itr->first << "\n";
            output_count++;
        }
    }
}

template <class T>
void bst_remove_duplicates(map<T,int>& s, ostream& ostr, int& output_count)
{
    output_count = s.size();
    //loop thru all elements
    for (int i = 0; i < s.size(); i++)
    {
        for (typename map<T,int>::iterator itr = s.begin(); itr != s.end(); itr++)
        {
            //output in order based on order of input
            if (itr->second == i)
            {
                ostr << itr->first << "\n";
                break;
            }
        }
    }
    
}

template<class T>
void bst_mode(map<T,int>& s, ostream& ostr, int& output_count)
{
    int maxcount = 0;
    output_count = 1;
    typename map<T, int>::iterator it = s.begin();
    //already have a count of elements so just loop thru
    for (typename map<T, int>::iterator itr = s.begin(); itr != s.end(); itr++)
    {
        //set max accordingly
        if (itr->second > maxcount)
        {
            maxcount = itr->second;
            it = itr;
        }
    }
    ostr << it->first << "\n";
}

void bst_closest_pair(set<int>& s, ostream& ostr, int& output_count)
{
    assert(s.size() >= 2);
    output_count = 2;
    int best;
    typename set<int>::iterator best_itr = s.end();

    //2 iterators to keep track of 1 from the end
    typename set<int>::iterator itr = s.begin();
    typename set<int>::iterator itr2 = s.begin();
    itr2++;

    //Keep going until 1 less than end of list
    while (itr2 != s.end())
    {
        int diff = (*itr2) - (*itr);

        //check if difference between close pairs is the closest
        if (best_itr == s.end() || diff < best) {
            best = diff;
            best_itr = itr;
        }

        //iterate
        itr++;
        itr2++;
    }
    output_count = 2;
    ostr << (*best_itr) << "\n";
    best_itr++;
    ostr << ((*best_itr)) << "\n";
}

template <class T>
void bst_first_sorted(map<T,int>& s, ostream& ostr, int& output_count, int optional_arg)
{
    assert(optional_arg >= 1);
    assert((int)s.size() >= optional_arg);
    output_count = optional_arg;
    int count = 0;
    for (typename map<T,int>::iterator itr = s.begin(); itr != s.end(); itr++)
    {
        if (count < optional_arg)
        {
            for (int i = 0; i < itr->second; i++)
            {
                if (count < optional_arg)
                {
                    ostr << itr->first << "\n";
                    count++;
                }
                else
                {
                    break;
                }
               
            }
        }
        else
        {
            break;
        }
    }
}
void bst_longest_substring(set<string>& s, ostream& ostr, int& output_count)
{
    //IMPLEMENT
}
void bst_test(const std::string &operation, const std::string &type,
              std::istream &istr, std::ostream &ostr,
              int &input_count, int &output_count, int optional_arg) {

    if (type == "string") {
        // load the data into a map or set of strings
        map<string, int> duplicateTest;
        map<string, int> modeTest;
        std::set<std::string> setTest;
        std::string s;
        input_count = 0;
        int count = 0;
        while (istr >> s) {
            if (duplicateTest.find(s) == duplicateTest.end())
            {
                duplicateTest.insert(pair<string, int>(s, count));
                count++;
            }
            setTest.insert(s);
            modeTest[s]++;
            input_count++;
        }
        if (operation == "sort") { bst_sort(modeTest, ostr, output_count); }
        else if (operation == "remove_duplicates") { bst_remove_duplicates(duplicateTest, ostr, output_count); }
        else if (operation == "mode") { bst_mode(modeTest, ostr, output_count); }
        // "closest_pair" not available for strings
        else if (operation == "first_sorted") { bst_first_sorted(modeTest, ostr, output_count, optional_arg); }
        //else if (operation == "longest_substring") { bst_longest_substring(setTest, ostr, output_count); }
        else { std::cerr << "Error: Unknown operation: " << operation << std::endl; usage(); exit(0); }
    }
    
    else {
        assert(type == "integer");
        // load the data into a map or set of integers
        map<int, int> duplicateTest;
        map<int, int> modeTest;
        set<int> setTest;
        int v;
        int count = 0;
        input_count = 0;
        while (istr >> v) {
            if (duplicateTest.find(v) == duplicateTest.end())
            {
                duplicateTest.insert(pair<int, int>(v, count));
                count++;
            }
            setTest.insert(v);
            modeTest[v]++;
            input_count++;
        }
        if (operation == "sort") { bst_sort(modeTest, ostr, output_count); }
        else if (operation == "remove_duplicates") { bst_remove_duplicates(duplicateTest, ostr, output_count); }
        else if (operation == "mode") { bst_mode(modeTest, ostr, output_count); }
        else if (operation == "closest_pair") { bst_closest_pair(setTest, ostr, output_count); }
        else if (operation == "first_sorted") { bst_first_sorted(modeTest, ostr, output_count, optional_arg); }
        // "longest_substring" not available for integers
        else { std::cerr << "Error: Unknown operation: " << operation << std::endl; usage(); exit(0); }
    }
    
}
