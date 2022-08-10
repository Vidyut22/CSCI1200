using namespace std;
#include <iostream>
#include <map>
#include <string>
#include <fstream>

int main(int argc, char* argv[])
{
	fstream my_file;
	my_file.open(argv[1], ios::in);
	if (!my_file) {
		cout << "No such file";
		return 0;
	}
	int key;
	map <int, int> mode;
	while (my_file >> key)
	{
		++mode[key];
	}
	int max;
	map<int, int>::const_iterator it;
	for (it = mode.begin(); it != mode.end(); ++it) 
	{
		if (it->second > max)
		{
			max = it->second;
		}
	}
	cout << "The modes are:" << endl;
	for (it = mode.begin(); it != mode.end(); ++it)
	{
		if (it->second == max)
		{
			cout << it->first << endl;
		}
	}
	return argc;
}