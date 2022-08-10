using namespace std;
#include <iostream>
#include <cmath>
#include<string>
#include <vector>
int foobar(const vector<string>& a, int b)
{
	int answer = 0;
	for (int i = 0; i < (int)a.size(); i += b)
	{
		answer++;
	}
	return answer;
}
vector<int> bar2(const vector<string>& a)
{
	vector<int> answer;
	for (int i = 0; i < (int)a.size(); i++)
	{
		answer.push_back(a[i].size());
	}
	return answer;
}
vector<string> bar3(const vector<int>& a)
{
	vector<string> answer;
	for (int i = 0; i < (int)a.size(); i++)
	{
		answer.push_back(string(a[i], '+'));
	}
	return answer;
}
void bar3(vector<string>& a, const string& b)
{
	for (int i = 0; i < (int)a.size(); i++)
	{
		a[i] = b;
	}
}
vector<int> bar4(const vector<string>& a)
{
	vector<int> answer;
	if (!a.empty())
	{
		for (int i = 0; i < (int)min(a[0].size(), a.size()); i++)
		{
			answer.insert(answer.begin(), a[i].size());
		}
	}
	return answer;
}
void bar5(vector<int>& a)
{
	for (int i = 0; i < (int)a.size(); i++)
	{
		if (a[i] > 0)
		{
			a.erase(a.begin() + i);
			i--;
		}
	}
}
int main()
{
	vector<int>a = { 1,2,3,4,5 };
	vector<string>str = { "foo","foo","bar","foo","foo","bar", "foo","foo","bar","foo","foo","bar" };
	int num = 21;
	string b = "vidyut";
	//foobar(str, num);
	bar2(str);
	//bar3(a);
	//bar3(str, b);
	//bar4(str);
	//bar5(a);
	return 0;
}