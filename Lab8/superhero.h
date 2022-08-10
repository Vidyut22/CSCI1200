#include <string>
#include <iostream>
using namespace std;
class Superhero
{
public:
	Superhero(string supername, string name, string power);
	string getName();
	string getPower();
	//strint Team();
	bool operator==(string str);
	bool operator!=(string str);
	void operator -();
	bool operator >(const Superhero& superhero);
	
	bool isGood();
private:
	string getTrueIdentity();
	string supername;
	string name;
	string power;
	bool good;
};
ostream& operator<<(ostream& os,Superhero& superhero);

