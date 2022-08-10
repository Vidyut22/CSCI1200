using namespace std;
#include <fstream>
#include <iostream>
#include <list>
#include <vector>

int pathFinder(int x, int y) 
{
	if (x == 0 || y == 0)
	{
		return 1;
	}
	return pathFinder(x - 1, y) + pathFinder(x, y - 1);
}

void print(int num)
{
	cout << num << endl;
}

int main() 
{
	for (int i = 0; i < 18; i++)
	{
		cout << "(" << i << "," << i << "): ";
		print(pathFinder(i, i));
	}

	cout << "2147483647 ---> ABOUT MAX INT VALUE" << endl;
}