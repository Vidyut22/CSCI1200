#include <cassert>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <string>
#include <queue>
using namespace std;

// defined in performance.cpp
void usage();
template <class T>
void priority_queue_sort(priority_queue<T, vector<T>, greater<T>>& pq, ostream& ostr, int& output_count)
{
    output_count = 0;
    for (unsigned int i = pq.size() - 1; i >= 0; i--) {
        ostr<<pq.top()<<"\n"; //add the top value
        output_count++;
        if (pq.size() > 1)
            pq.pop(); //remove the top value to access the next value (if possible)
        else
            break; //no values left to add
    }
}

template <class T>
void priority_queue_remove_duplicates(priority_queue<T, vector<T>, greater<T>>& pq, ostream& ostr, int& output_count)
{
    ostr << "UNREASONABLE TASK FOR HASH TABLE. (DEFIES PURPOSE)" << endl;
}

template<class T>
void priority_queue_mode(priority_queue<T, vector<T>, greater<T>> &pq, ostream& ostr, int& output_count)
{
    T prev = pq.top();
    pq.pop();

    //tracking the mode, current count
    T mode;
    int current_count = 1;
    int mode_count = 0;

    //while values are still in the queue
    while (pq.size() > 0) 
    {
        //if the current value equals the previous, increase its count
        if (pq.top() == prev) {
            current_count++;
        }
        //assess if the previous values are the new mode
        else if (current_count > mode_count) {
            mode = prev;
            mode_count = current_count;
            current_count = 1;
        }
        else {
            current_count = 1;
        }
        //reassign prev and remove it in order to access next value in queue
        prev = pq.top();
        pq.pop();
    }

    //final check to assess if the previous values are the new mode
    if (current_count > mode_count) {
        mode = prev;
        mode_count = current_count;
    }

    //output data
    output_count = 1;
    ostr << mode << "\n";
}

void priority_queue_closest_pair (priority_queue<int, vector<int>, greater<int>> &pq, ostream& ostr, int& output_count)
{
    assert(pq.size() >= 2);
    int prev = pq.top();
    pq.pop();
    int best = -1;
    int first;
    int second;
    //loop while continuously popping tree
    while (pq.size() > 0)
    {
        int diff = abs(prev - pq.top());
        //check to assess if current difference is the least
        if ((best == -1 || diff < best) && (diff!= 0))
        {
            second = pq.top();
            first = prev;
            best = diff;
        }
        //set previous max and pop to get new max
        prev = pq.top();
        pq.pop();
    }
    output_count = 2;
    ostr << first << "\n";
    ostr << second << "\n";
}

template <class T>
void priority_queue_first_sorted(priority_queue<T, vector<T>, greater<T>>& pq, ostream& ostr, int& output_count, int optional_arg)
{
    output_count = 0;
    for (unsigned int i = 0; i < optional_arg; i++) {
        ostr << pq.top() << "\n"; 
        pq.pop();
    }
}

void priority_queue_longest_substring(priority_queue<string>& lst, std::ostream& ostr, int& output_count)
{
    //IMPLEMENT
}

void priority_queue_test(const std::string &operation, const std::string &type,
                         std::istream &istr, std::ostream &ostr,
                         int &input_count, int &output_count, int optional_arg) 
{
    if (type == "string")
    {
        priority_queue<string,vector<string>, greater<string>> pq;
        string s;
        input_count = 0;
        while (istr >> s)
        {
            pq.push(s);
            input_count++;
        }
        if (operation == "sort") { priority_queue_sort(pq, ostr, output_count); }
        else if (operation == "remove_duplicates") { priority_queue_remove_duplicates(pq, ostr, output_count); }
        else if (operation == "mode") { priority_queue_mode(pq, ostr, output_count); }
        // "closest_pair" not available for strings
        else if (operation == "first_sorted") { priority_queue_first_sorted(pq, ostr, output_count, optional_arg); }
        //else if (operation == "longest_substring") { list_longest_substring(lst, ostr, output_count); }
        else { std::cerr << "Error: Unknown operation: " << operation << std::endl; usage(); exit(0); }
    }
    else {
        assert(type == "integer");
        // load the data into a prio queue of integers
        priority_queue<int, vector<int>, greater<int>> pq;
        int v;
        input_count = 0;
        while (istr >> v) {
            pq.push(v);
            input_count++;
        }
        if (operation == "sort") { priority_queue_sort(pq, ostr, output_count); }
        else if (operation == "remove_duplicates") { priority_queue_remove_duplicates(pq, ostr, output_count); }
        else if (operation == "mode") { priority_queue_mode(pq, ostr, output_count); }
        else if (operation == "closest_pair") { priority_queue_closest_pair(pq, ostr, output_count); }
        else if (operation == "first_sorted") { priority_queue_first_sorted(pq, ostr, output_count, optional_arg); }
        // "longest_substring" not available for integers
        else { std::cerr << "Error: Unknown operation: " << operation << std::endl; usage(); exit(0); }
    }
}
