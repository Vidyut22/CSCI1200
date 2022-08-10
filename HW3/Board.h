#ifndef Board_h_
#define Board_h_
#include <iostream>
#include <string>
using namespace std;
class Board
{
public:
	//CONSTRUCTOR, DESTRUCTOR, ASSIGNMENT OPERATOR
	Board();
	Board(string P1T, string P2T, string Fill);
	Board(const Board& b);
	~Board();
	Board& operator=(const Board& b);
	//MEMBER FUNCTIONS AND OTHER OPERATORS
	const string& getPlayer1Token();
	const string& getPlayer2Token();
	const string& getFill();
	const int& numRows();
	const int& numColumns();
	int numTokensInRow(int row) const;
	int numTokensInColumn(int col) const;
	string insert(int col, bool player);
	void clear();
	string** getData();
	
	

private:
	//PRICATE MEMBER FUNCTIONS
	bool connectFour(const int &col, const string &player); //only use within insert (after each token is placed)
	string** create();
	int* setSize();
	void resize(const int& col);
	void copy(const Board& b);
	//REPRESENTATION
	string** m_data; // Pointer to first location in allocated array of pointers
	int* size; // Pointer to first location in array of sizes
	int rows; // Number of rows on board
	int cols; //Number of coloumns on board
	string P1T; // Player 1's token
	string P2T; // Player 2's token
	string Fill; // Background token
};
//ASSIGNMENT OPERATOR <<
ostream& operator<<(ostream& COUT, Board& b);
#endif
