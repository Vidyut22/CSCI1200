using namespace std;

/// <summary>
/// Zone object is used to keep track of the number of stars in a given zone
/// </summary>
class Zone
{
public:
	//DEFAULT CONSTRUCTOR
	Zone(char zone);

	//ACCESSORS
	char getZone()
	{
		return zone;
	}
	unsigned int getcountStar()
	{
		return countStar;
	}
	//SETTERS
	void updateCount(int num)
	{
		countStar = countStar + num;
	}
private:
	//MEMBER VARIABLES
	char zone;
	unsigned int countStar;
};