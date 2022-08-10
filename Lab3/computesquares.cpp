using namespace std;
#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
void compute_squares(unsigned int *a, unsigned int *b, unsigned int n)
{
	for (int i = 0; i <(int) n; i++)
	{
		*(b + i)=*(a + i)* *(a + i) ;
	}
}
int main()
{
	unsigned int n = 2;
	unsigned int a[n] = {65535,65536 };
	unsigned int b[n] = {0};
	compute_squares(a,b,n);
		for (int i = 0; i < (int)n; i++)
		{
			cout << *(b+i) << endl;
		}
}