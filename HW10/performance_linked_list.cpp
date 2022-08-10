#include <cassert>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <string>
#include <list>
using namespace std;

// defined in performance.cpp
void usage();

template <class T>
void list_sort(list<T>& lst, ostream& ostr, int& output_count)
{
    lst.sort();
    output_count = lst.size();
    for (typename list<T>::iterator itr = lst.begin(); itr != lst.end(); itr++)
    {
        cout << (*itr) << "\n";
    }
}
template <class T>
void list_remove_duplicates(std::list<T>& lst, std::ostream& ostr, int& output_count)
{
    output_count = 0;
    //Loop thru all elements in list
    for (typename list<T>::iterator itr = lst.begin(); itr != lst.end(); itr++)
    {
        bool dup = false;
        //Check everyother elemenet for repitition
        for (typename list<T>::iterator itr2 = lst.begin(); itr2 != itr; itr2++)
        {
            if ((*itr) == (*itr2))
            {
                dup = true;
                break;
            }
        }
        //If there is no duplicate output
        if (!dup)
        {
            ostr << (*itr) << "\n";
            output_count++;
        }
    }
}

template<class T>
void list_mode(list<T>& lst, ostream& ostr, int& output_count)
{
    //empty list
    if (lst.begin() == lst.end())
    {
        ostr << "EMPTY LIST" << "\n";
        return;
    }
    lst.sort();
    int max_count = 0;
    int count = 0;
    T mode =  *lst.begin();
    typename list<T>::iterator it = lst.begin();

    //loop thru all elements in list
    for (typename list<T>::iterator itr = lst.begin(); itr != lst.end(); itr++)
    {
        //check if current element is still equal to previous element
        if ((*itr) != mode)
        {
            //set max accordingly
            if (count > max_count)
            {
                max_count = count;
                it = itr;
                it--;   
            }
            mode = (*itr);
            count = 1;
        }
        else
        {
            count++;
        }
    }
    output_count = 1;
    ostr << (*it) << "\n";
}

void list_closest_pair(list<int>& lst, ostream& ostr, int& output_count)
{
    assert(lst.size() >= 2);
    lst.sort(); //sort
    output_count = 2;
    int best;
    typename list<int>::iterator best_itr = lst.end();

    //2 iterators to keep track of 1 from the end
    typename list<int>::iterator itr = lst.begin();
    typename list<int>::iterator itr2 = lst.begin();
    itr2++;
    //Keep going until 1 less than end of list
    while(itr2!=lst.end())
    {
        int diff = (*itr2) - (*itr);
        //check if difference between close pairs is the closest
        if (best_itr == lst.end() || diff < best)
        {
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
void list_first_sorted(list<T>& lst, ostream& ostr, int& output_count, int optional_arg)
{
    assert(optional_arg >= 1);
    assert((int)lst.size() >= optional_arg);
    lst.sort();
    typename list<T>::iterator itr = lst.begin();
    for (int i = 0; i < optional_arg; i++)
    {
        ostr << (*itr) << "\n";
        itr++;
    }
}

void list_longest_substring(list<string>& lst, std::ostream& ostr, int& output_count)
{
    //IMPLEMENT
}

void list_test(const std::string &operation, const std::string &type,
                 std::istream &istr, std::ostream &ostr,
                 int &input_count, int &output_count, int optional_arg) {

  // HINT: For the string element type, declare your list like this:
  // std::list<std::string> lst;
    if (type == "string")
    {
        list<string>lst;
        string s;
        input_count = 0;
        while (istr >> s)
        {
            lst.push_back(s);
            input_count++;
        }
        if (operation == "sort") { list_sort(lst, ostr, output_count); }
        else if (operation == "remove_duplicates") { list_remove_duplicates(lst, ostr, output_count); }
        else if (operation == "mode") { list_mode(lst, ostr, output_count); }
        // "closest_pair" not available for strings
        else if (operation == "first_sorted") { list_first_sorted(lst, ostr, output_count, optional_arg); }
        //else if (operation == "longest_substring") { list_longest_substring(lst, ostr, output_count); }
        else { std::cerr << "Error: Unknown operation: " << operation << std::endl; usage(); exit(0); }
    }
    else {
        assert(type == "integer");
        // load the data into a list of integers
        std::list<int> lst;
        int v;
        input_count = 0;
        while (istr >> v) {
            lst.push_back(v);
            input_count++;
        }
        if (operation == "sort") { list_sort(lst, ostr, output_count); }
        else if (operation == "remove_duplicates") { list_remove_duplicates(lst, ostr, output_count); }
        else if (operation == "mode") { list_mode(lst, ostr, output_count); }
        else if (operation == "closest_pair") { list_closest_pair(lst, ostr, output_count); }
        else if (operation == "first_sorted") { list_first_sorted(lst, ostr, output_count, optional_arg); }
        // "longest_substring" not available for integers
        else { std::cerr << "Error: Unknown operation: " << operation << std::endl; usage(); exit(0); }
    }
}
