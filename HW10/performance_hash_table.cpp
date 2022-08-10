#include <cassert>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_set>
#include <unordered_map>
using namespace std;

// defined in performance.cpp
void usage();

template <class T>
void hash_table_sort(unordered_map<T,int> &table, ostream &ostr, int &output_count)
{
    ostr << "UNREASONABLE TASK FOR HASH TABLE. (DEFIES PURPOSE)" << endl;
}

template <class T>
void hash_table_remove_duplicates(unordered_map<T,int>& table, ostream& ostr, int& output_count)
{
    output_count = table.size();
    //map contains value | count
    //loop thru table but only couput once regardless of count
    for (int i = 0; i < table.size(); i++)
    {
        for (typename unordered_map<T, int>::iterator itr = table.begin(); itr != table.end(); itr++)
        {
            if (itr->second == i)
            {
                ostr << itr->first << "\n";
                break;
            }
        }
    }
}

template <class T>
void hash_table_mode(unordered_map<T,int>& table, ostream& ostr, int& output_count)
{
    int maxcount = 0;
    output_count = 1;
    typename unordered_map<T, int>::iterator it = table.begin();

    //Loop thru all elements in table
    for (typename unordered_map<T, int>::iterator itr = table.begin(); itr != table.end(); itr++)
    {
        //check if currenet elements count is greater than max
        if (itr->second > maxcount)
        {
            //set accordingly
            maxcount = itr->second;
            it = itr;
        }
    }
    ostr << it->first << "\n";
}
void hash_table_closest_pair(unordered_set<int>& table, ostream& ostr, int& output_count)
{
    assert(table.size() >= 2);
    output_count = 2;
    int best;
    typename unordered_set<int>::iterator best_itr = table.end();
    typename unordered_set<int>::iterator best_itr2 = table.begin();

    //2 iterators to keep track of 1 from the end
    typename unordered_set<int>::iterator itr = table.begin();
    typename unordered_set<int>::iterator itr2 = table.begin();
    itr2++;

    //Keep going until 1 less than end of list
    for (; itr2 !=table.end(); itr++)
    {
        itr2++;
        //Check each other value in table
        for (; itr2 != table.end(); itr2++)
        {
            //check if difference between close pairs is the closest
            int diff = abs((*itr) - (*itr2));
            if (best_itr == table.end() || diff < best)
            {
                best = diff;
                best_itr = itr;
                best_itr2 = itr2;
            }
        }
        //iterate
        itr2 = itr;
        itr2++;
    }
    //Output
    output_count = 2;
    if (*best_itr < *best_itr2)
    {
        ostr << *best_itr << "\n";
        ostr << *best_itr2 << "\n";
    }
    else
    {
        ostr << *best_itr2 << "\n";
        ostr << *best_itr << "\n";
    }
}
template <class T>
void hash_table_first_sorted(unordered_map<T,int>& table, ostream& ostr, int& output_count, int& optional_arg)
{
    ostr << "UNREASONABLE TASK FOR HASH TABLE. (DEFIES PURPOSE)" << endl;
}
void hash_table_longest_substring(unordered_map<string,int>& s, ostream& ostr, int& output_count)
{
    //IMPLEMENT
}
void hash_table_test(const std::string &operation, const std::string &type,
                     std::istream &istr, std::ostream &ostr,
                     int &input_count, int &output_count, int optional_arg) {

    if (type == "string") {
        // load the data into a unordered map or set of strings
        unordered_map<string, int> modeTest;
        unordered_set<string> setTest;
        unordered_map<string, int> duplicateTest;
        string s;
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
        if (operation == "sort") { hash_table_sort(modeTest, ostr, output_count); }
        else if (operation == "remove_duplicates") { hash_table_remove_duplicates(duplicateTest, ostr, output_count); }
        else if (operation == "mode") { hash_table_mode(modeTest, ostr, output_count); }
        // "closest_pair" not available for strings
        else if (operation == "first_sorted") {hash_table_first_sorted(modeTest, ostr, output_count, optional_arg); }
        //else if (operation == "longest_substring") { hash_table_longest_substring(setTest, ostr, output_count); }
        else { std::cerr << "Error: Unknown operation: " << operation << std::endl; usage(); exit(0); }
    }

    else {
        assert(type == "integer");
        // load the data into a unordered map or set  of integers
        unordered_map<int, int> modeTest;
        unordered_set<int> setTest;
        unordered_map<int, int> duplicateTest;
        int v;
        input_count = 0;
        int count = 0;
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
        if (operation == "sort") { hash_table_sort(modeTest, ostr, output_count); }
        else if (operation == "remove_duplicates") { hash_table_remove_duplicates(duplicateTest, ostr, output_count); }
        else if (operation == "mode") { hash_table_mode(modeTest, ostr, output_count); }
        else if (operation == "closest_pair") { hash_table_closest_pair(setTest, ostr, output_count); }
        else if (operation == "first_sorted") { hash_table_first_sorted(modeTest, ostr, output_count, optional_arg); }
        // "longest_substring" not available for integers
        else { std::cerr << "Error: Unknown operation: " << operation << std::endl; usage(); exit(0); }
    }
}
