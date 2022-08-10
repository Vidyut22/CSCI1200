using namespace std;
#include "Board.h"
#include <iostream>
#include <stdlib.h>
#include <string>
//Default Constructor, assign all representation values
Board::Board(string P1T, string P2T, string Fill)
{
	this->P1T = P1T;
	this->P2T = P2T;
	this->Fill = Fill;
	rows = 5;
	cols = 4;
	m_data = create();
	size = setSize();
	
}
//Copy Constructor
Board::Board(const Board& b)
{
	copy(b);
}
// Create the Board as a copy of the given Board
void Board::copy(const Board& b)
{
	this->P1T = b.P1T;
	this->P2T = b.P2T;
	this->Fill = b.Fill;
	this->rows = b.rows;
	this->cols = b.cols;
	this->size = new int[cols];
	this->m_data = new string * [cols];

	// Copy the data
	for (int i = 0; i < (int)this->cols; i++)
	{
		this->size[i] = b.size[i];

		//Allocate correct slots of memory to each column pointer of board
		if (size[i] > 0)
		{
			this->m_data[i] = new string[b.numTokensInColumn(i)];
		}
		for (int j = 0; j < b.numTokensInColumn(i); j++)
		{	
			this->m_data[i][j] = b.m_data[i][j];
		}
	}
}
// Assign one board to another and deleting old memory
Board& Board::operator=(const Board& b) {
	if (this != &b) {
		for (int i = 0; i < cols; i++)
		{
			if (size[i] > 0)
			{
				delete[] m_data[i];
			}
		}
		delete[] size;
		delete[] m_data;
		this->copy(b);
	}
	return *this;
}
//Return Player 1's Token String
const string& Board::getPlayer1Token() 
{
	return P1T;
}
//Return Player 2's Token String
const string& Board::getPlayer2Token() //return player 2's string
{
	return P2T;
}
//Return Background Token String
const string& Board::getFill()
{
	return Fill;
}
//Return Number of Rows
const int& Board::numRows()
{
	return rows;
}
//Return Number of Columns
const int& Board::numColumns()
{
	return cols;
}
//Return number of tokens by either player in row given by user
int Board::numTokensInRow(int row) const
{
	if (row + 1 <= rows)
	{
		int num = 0;
		for (int i = 0; i < cols; i++)
		{
			if (size[i] - 1 >= row)
			{
				num++;
			}
		}
		return num;
	}
	return -1;
}
//Return number of tokens by either player in column given by user
int Board::numTokensInColumn(int col) const
{
	if (col + 1 <= cols)
	{
		return size[col];
	}
	else
	{
		return -1;
	}
}
// Insert an element to the Board at the column given from user
string Board::insert(int col, bool player)
{
	string currPlayer;

	//Realloacte memory depending on location of token
	resize(col);

	//Set token string of player chose
	if (player)
	{
		currPlayer = P1T;
	}
	else
	{
		currPlayer = P2T;
	}

	//Insert the token into the 2D array Board
	m_data[col][size[col] - 1] = currPlayer;

	//Check if there is a connect four
	if(connectFour(col, currPlayer))
	{
		return currPlayer;
	}
	return Fill;
	
}
// If col is greater than the current number of coloumns, change the size of array of
// pointers. Regardless, the size of array[col] of strings needs to increase by 1
// In all situations, reallocation should occur on pointers or data.
void Board::resize(const int& col)
{
	// Check if the new token will extend the coloumn allocation
	if (col > cols - 1)
	{
		int tmp = cols;
		cols = col + 1;
		// Allocate memory for Board representation based on new size
		string** new_data = new string * [cols];
		int* new_size = new int [cols];

		//Copy values of previous allocation to new allocation space
		for (int i = 0; i < cols; i++)
		{	
			if (i < tmp)
			{
				new_data[i] = m_data[i];
				new_size[i] = size[i];
			}
			//Set size of new coloumns
			else
			{
				new_size[i] = 0;
			}

		}
		//Delete old memory and set pointers to new allocation
		delete[] size;
		size = new_size;
		delete[] m_data;
		m_data = new_data;
	}
	size[col]++;

	// Allocate new memory for specific array of strings
	string* new_col = new string[size[col]];

	// Copy values of previous allocation to new allocation space
	for (int i = 0; i < size[col]-1; i++)
	{
		new_col[i] = m_data[col][i];
	}

	//Delete old memory and set pointer to new allocation
	if (size[col]-1 > 0)
	{
		delete[] m_data[col];
	}
	m_data[col] = new_col;
	if (size[col] > rows)
	{
		rows++;
	}
}

// Complete 2 checks for a vertical and horizontal connect four. 
// Vertical: If there are more than 4 tokens below the current spot, check
// for 3 more of the same token below current spot
// Horizontal: Complete 2 checks for left and right of the current token
// ---Left: Keep going left until next left string is not same as the players token
// -------- or run out of columns. (switch to right)
// ---Right:Keep going right until next right string is not same as the players token
// -------- or run out of coloumns. Check if the count of correct tokens is = 4
// Do not access unassigned memory!
bool Board::connectFour(const int &col, const string&player)
{
	//Vertical Connect 4 Check
	int count = 1;

	//Keep count of the number of similar tokens directly below and check if its = to 4
	if (size[col] >= 4)
	{
		for (int i = 1; i < 4; i++)
		{
			if (m_data[col][size[col] - (i + 1)] == player)
			{
				count++;
			}
			else
			{
				break;
			}
		}
		if (count == 4)
		{
			return true;
		}
	}
	//Horizontal Connect 4 Check
	count = 1;
	int iterator = 0;
	bool left = true;

	//Keep checking until count limit has been reached
	while (count < 4)
	{
		// Left side
		// Use iterator to keep shifting left by one coloumn
		if (left)
		{
			if (col + (iterator-1)>=0 ) //Enough remaing coloumns
			{
				if (size[col + (iterator-1)] >= size[col]) //Enough tokens in coloumn to left
				{
					iterator--;
					if (m_data[col + iterator][size[col] - 1] == player)
					{
						count++;
					}
					else
					{
						left = false;
						iterator = 0;
					}
				}
				else
				{
					left = false;
					iterator = 0;
				}
			}
			else
			{
				left = false;
				iterator = 0;
			}
		}
		// Right side
		// Use iterator to keep shifting right by one coloumn
		else
		{
			if (cols - (col + 1) >= (4 - count)) //Enough remaing coloumns
			{
				if (size[col + (iterator+1)] >= size[col]) //Enough tokens in coloumn to left
				{
					iterator++;
					if (m_data[col + iterator][size[col] - 1] == player)
					{
						count++;
					}
					else
					{
						break;
					}
				}
				else
				{
					break;
				}
			}
			else
			{
				break;
			}
		}
	}
	return count == 4;
}

// Create double pointer of strings with allocated size of # columns (2d array of Board)
string** Board::create()
{
	string** board = new string* [cols];
	return board;
}
// Create pointer of ints with allocated size of # columns (Initialize sizes to 0)
int* Board::setSize()
{
	int* size = new int[cols];
	for (int i = 0; i < cols; i++)
	{
		size[i] = 0;
	}
	return size;
}
// Delete allocated memory and re-assign the representation of Board to default
void Board::clear()
{
	for (int i = 0; i < cols; i++)
	{
		delete[] m_data[i];
	}
	delete[] size;
	delete[] m_data;
	rows = 5;
	cols = 4;
	m_data = create();
	size = setSize();
}

//Return double pointer of Board
string** Board::getData()
{
	return m_data;
}
//Delete all allocated memory
Board::~Board()
{
	for (int i = 0; i < cols; i++)
	{
		if (size[i] > 0)
		{
			delete[] m_data[i];
		}
	}
	delete[] m_data;
	delete[] size;
}
// Assign operator << to be compatiable with object Board
ostream& operator<<(ostream& COUT,Board& b)
{
	// Print in order of top row to bottom row
	for (int i = b.numRows() - 1; i >= 0; i--)
	{
		string str = "";
		//Print in order of left to right
		for (int j = 0; j < b.numColumns(); j++)
		{
			if (b.numTokensInColumn(j)>=i+1)
			{
				str += b.getData()[j][i];
				if (j != b.numColumns() - 1)
				{
					str += " ";
				}
			}
			// If memory hasn't been allocated for given loction use fill token
			else
			{
				str += b.getFill();
				if (j != b.numColumns() - 1)
				{
					str += " ";
				}
			}
		}
		COUT << str << endl;
	}
	return COUT;
}