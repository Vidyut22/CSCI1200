/*
These two functions are not required for your program, but may be helpful!
The recursive function will generate every combination of 0/1 for 6 positions
in a vector. Whenever pos == 6, the vector is complete.

Hint: There are 6 different "fields" in a query, this may be useful in constructing
your hash table.
*/
#include <iostream>
#include <vector>
using namespace std;

void permute_filters(int pos, std::vector<int> filter, vector<vector<int>> & combos){
	if(pos == 6){
		combos.push_back(filter);
		return;
	}

	filter.push_back(0);
	std::vector<int> filter_new = filter;
	filter_new.back() = 1;
	permute_filters(pos+1, filter_new,combos);
	permute_filters(pos+1, filter,combos);
}

//Driver function, feel free to modify to pass more arguments
vector<vector<int>> permute_filters(){
	vector<int> test;
	vector<vector<int>> combos;
	permute_filters(0, test, combos);
	return combos;
}

int main()
{
	vector<vector<int>> combos = permute_filters();
	for (unsigned int i = 0; i < combos.size(); i++)
	{
		for (unsigned int j = 0; j < combos[i].size(); j++)
		{
			cout << combos[i][j];
		}
		cout << endl;
	}
}