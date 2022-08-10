#ifndef hashmap
#define hashmap
#include "Query.h"
#include "Movie.h"
#include <iostream>
#include <list>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

typedef vector<pair<Query, list<Movie>>> tableRep;
class HashMap
{
public:
    //CONSTRUCTORS
    HashMap(unsigned int init_size = 100) : m_table(init_size), m_size(0), occupancy(0.5) 
    {
        permutations = permute_filters();
    }
    //COPY
    HashMap(const HashMap& old)
        : m_table(old.m_table), m_size(old.m_size), occupancy(old.occupancy), permutations(old.permutations) {}

    //DESTRUCTOR
    ~HashMap() {}

    //SETTERS
    // Set size of map
    void setSize(unsigned int init_size)
    {
        tableRep newM_table(init_size);
        m_table = newM_table;
    }
    // Set occupancy of map
    void setOccupancy(float init_occupancy)
    {
        occupancy = init_occupancy;
    }
    // Set map of actor alias and actual name
    void setActorMap(map<string, string>&m)
    {
        actorMap = m;
    }

    // ACCESSORS
    unsigned int size() const
    {
        return m_size;
    }

    /*
    Method to insert a pair of key and movie into map.
    Returns if it was able to insert and an iterator to
    insertion position.
    */
    pair<bool, tableRep::iterator> insert(Query key,Movie movie)
    {
        //If the size is greter than occupancy resize table
        if (m_size >= occupancy * m_table.size())
        {
            this->resize_table(2 * m_table.size() + 1); 
        }
        //Create index
        unsigned int hash_value = key.hash();
        unsigned int index = hash_value % m_table.size();

        //Loop until found empty position
        while (!isEmpty(m_table[index]))
        {
            //If found same query, only add movie
            if (m_table[index].first == key)
            {
                m_table[index].second.push_back(movie);
                tableRep::iterator itr = m_table.begin() + index;
                return make_pair(true,itr);
            }
            index++;
            if (index >= m_table.size())
            {
                index = 0;
            }
        }
        //Add query and movie into map
        m_table[index].first = key;
        m_table[index].second.push_front(movie);
        m_size++;
        //Return position
        tableRep::iterator itr = m_table.begin() + index;
        return make_pair(true, itr);
    }

    /*
    Method to find position of given query. If query is found,
    first position is true, if not it is false. Second postion
    is iterator to map
    */
    pair<bool, tableRep::iterator> find(Query key)
    {
        //Create index based on hash value and size
        unsigned int hash_value = key.hash();
        unsigned int index = hash_value % m_table.size();

        //Loop until find query in map
        while (m_table[index].first != key)
        {
            //If found empty pos add, not found
            if (isEmpty(m_table[index]))
            {
                tableRep::iterator itr = m_table.end();
                return make_pair(false, itr);
            }
            index++;
            if (index >= m_table.size())
            {
                index = 0;
            }
        }
        //Return position of query
        tableRep::iterator itr = m_table.begin() + index;
        return make_pair(true, itr);
    }

    /*
    Method to print out potential movies for a an iterator
    to a given query
    */
    void print(pair<bool,tableRep::iterator> qMovie)
    {
        //If couldn't find the query in map
        if (qMovie.first == false)
        {
            cout << "No results for query."<<endl;
            return;
        }
        //Store list of movies
        list<Movie>movie_list = (*qMovie.second).second;
        cout << "Printing " << movie_list.size() << " result(s):" << endl;

        //Loop thru all the potential movies for a given query
        for (list<Movie>::iterator itr = movie_list.begin(); itr != movie_list.end(); itr++)
        {
            cout << (*itr).getTitle() << endl;
            cout << (*itr).getYear() << endl;
            cout << (*itr).getRunTime() << endl;
            cout << (*itr).getGenres().size();

            //Print all genres
            vector<string>allGenres = (*itr).getGenres();
            for (unsigned int i = 0; i<allGenres.size();i++)
            {
                cout << " " << allGenres[i];
            }
            cout << endl;
            cout << (*itr).getActors().size();
            vector<string> tmpActors = (*itr).getActors();
            vector<string> tmpRoles = (*itr).getRoles();

            //Conjoin Actors and Roles together and print them
            for (unsigned int i = 0; i < tmpActors.size(); i++)
            {
                string aliasActor = "";
                //Find real name of actor gicen alias
                map<string, string>::iterator itr3 = actorMap.find(tmpActors[i]);
                if (itr3 != actorMap.end())
                {
                    aliasActor = itr3->second;
                }
                cout << " " << aliasActor << " (" << tmpRoles[i] << ")";
                
            }
            cout << endl;
        }
    }
    
    /*
    Method to populate hashmap with all possible queries for
    a given movie
    */
    void populateTable(Movie m)
    {
        //Loop through all 64 possible queries for given movie and add
        //them to the map
        for (unsigned int i = 0; i < permutations.size(); i++)
        {
            Query q;
            //Loop thru each category of query
            for (unsigned int j = 0; j < permutations[i].size(); j++)
            {
                //If current permutation position is 1 then include
                //that category in query. If not then don't include
                if (j == 0)
                {
                    if (permutations[i][j] == 1)
                    {
                        q.setTitle(m.getTitle());
                    }
                    else
                    {
                        q.setTitle("?");
                    }
                }
                else if (j == 1)
                {
                    if (permutations[i][j] == 1)
                    {
                        q.setYear(m.getYear());
                    }
                    else
                    {
                        q.setYear("?");
                    }
                   
                }
                else if (j == 2)
                {
                    if (permutations[i][j] == 1)
                    {
                        q.setRunTime(m.getRunTime());
                    }
                    else
                    {
                        q.setRunTime("?");
                    }

                }
                else if (j == 3)
                {
                    if (permutations[i][j] == 1)
                    {
                        q.setGenres(m.getGenres());
                    }
                }
                else if (j == 4)
                {
                    if (permutations[i][j] == 1)
                    {
                        q.setActors(m.getActors());
                    }
                   
                }
                else if (j == 5)
                {
                    if (permutations[i][j] == 1)
                    {
                        q.setRoles(m.getRoles());
                    }
                }
            }
            //Insert given query into map along with current movie
            //to be added to list of movies
            insert(q, m);
        }
    }
private:
    //PRIVATE MEMBER VARIABLES
    vector<pair<Query, list<Movie>>> m_table;
	unsigned int m_size;
	float occupancy;
    map<string, string> actorMap;
    vector<vector<int>> permutations;

    //PRIVATE HELPER METHODS

    /*
    Helper recurssion method to fill in vector of vector of integers
    of all possible combinations of 0/1 for 6 positions. This is used
    to determine all possible queries for a given movie
    */
    void permute_filters(int pos, vector<int> filter, vector<vector<int>>& combos) {
        //If reached 6th position, add 6 positions to combos
        if (pos == 6) {
            combos.push_back(filter);
            return;
        }

        filter.push_back(0);
        std::vector<int> filter_new = filter;
        filter_new.back() = 1;
        //Add 1 to the position of current permutation
        permute_filters(pos + 1, filter_new, combos);
        permute_filters(pos + 1, filter, combos);
    }

    //Driver Function (void Permute_filters)
    vector<vector<int>> permute_filters() {
        vector<int> test;
        vector<vector<int>> combos;
        //Call the recursive function with combos
        permute_filters(0, test, combos);
        return combos;
    }

    //Helper method to check if index in hashmap is empty
    bool isEmpty(const std::pair<Query,list<Movie>>& p)
    {
        return p == std::pair<Query, list<Movie>>();
    }

    //Private method to resize table if it reaches occupancy level
    void resize_table(unsigned int new_size) 
    {
        //Create new table of new size
        vector<pair<Query,list<Movie>>> newTable(new_size);

        //Loop thru current map size
        for (unsigned int i = 0; i < m_table.size(); i++)
        {
            if (!isEmpty(m_table[i]))
            {
                //Create new index value
                unsigned int hash_value = m_table[i].first.hash();
                unsigned int index = hash_value % new_size;
                //Loop until open position in map
                while (!isEmpty(newTable[index]))
                {
                    index++;
                    if (index == newTable.size())
                    {
                        index = 0;
                    }
                }
                //Insert pair into new position
                newTable[index] = m_table[i];
            }
           
        }
        //Reset map
        m_table = newTable;
    }
};
#endif
