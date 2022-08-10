using namespace std;
#include <vector>
#include <iostream>
#include <cassert>
#include <string>
#include "grid.h"	

typedef vector<Zone> zones;
typedef vector<vector<char>> gridchar;
typedef vector<vector<string>> gridstr;

//Initialization of member variables
//Class Initialization
Grid::Grid(int sVal, int rows, int cols, zones allZones, vector<gridstr> coordinates, bool mode)
{
	this->sVal = sVal;
	this->rows = rows; 
	this->cols = cols;
	this->allZones = allZones;
	this->mode = mode;
	grid_table = createGrid(coordinates);
	starBoard = createStarBoard();
	for (int i = 0; i < rows; i++)
	{
		rowCount.push_back(0);
	}
	for (int i = 0; i < cols; i++)
	{
		colCount.push_back(0);
	}
}

/// <summary>
/// This is the main reccursive solver method:
/// 
/// This method starts from the first cell on the board and goes left to right and then down, 
/// adding stars as it can. If it reaches the end of the board and there is no found solution, it
/// will delete the previous star and increment it forward (reccursive part), and re-try. This
/// will go all the way up the ladder of stars until the very first star gets placed at the end of the 
/// board meaning all possible combos have been checked
///  -> currS is the amount of stars currently on the board
/// </summary>
bool Grid::completeSolution(int row, int col, int currS) 
{
	//Check if the first star is at the last spot
	if (!(currS == 1 && atLastPos(row,col))) 
	{
		//if solution found add the star Board to a vector of starboards
		if (gridDone(currS))
		{
			solutionsGrid.push_back(starBoard); 
			// Cehck if need one or all solutions(mode true if all solutions needed)
			if (mode)
			{
				return false; 
			}
			return true;
			 
		}
		else
		{
			int cellsLeft = numCellsLeft(row, col);
			//loop thru all the potential remaining cells in the board 
			for (int i = 0; i < cellsLeft; i++) 
			{
				vector<int> newPos = nextPos(row, col);
				//Don't want to increment my position if there have not been any stars placed
				if (!(currS == 0 && i==0))
				{
					row = newPos[0];
					col = newPos[1];
				}
				//if you can add at the next position
				if (canAdd(row, col)) 
				{
					addStar(row, col);

					//call completeSolution again with an updated amount of stars on the board and updated current position
					bool finished = completeSolution(row, col, currS + 1); //Recursive call
					if (finished)
					{
						return true; //Done     went thru all possible solutions (on the top most level of recursion)
					}
					else
					{
						//delete previous star if all solutions have not been found
						deletePrevious(row, col); 
					}
				}

			}
			return false;
		}
	}
	else
	{
		//in the case there is only 1 cell
		if (gridDone(currS)) 
		{
			solutionsGrid.push_back(starBoard);
		}
		return true;
	}
	return true;
}
//Helper method to check if given position is at the end of the board
bool Grid::atLastPos(int row, int col)
{
	return (row == (int)starBoard.size() - 1 && col == (int)starBoard[row].size() - 1);
}

//Helper method that returns the number of cells remaining in the board from the given position
int Grid::numCellsLeft(int row, int col)
{
	return starBoard[0].size() - (col + 1) + starBoard[0].size() * (starBoard.size() - (row + 1));
}

//Helper method that returns of vector of size 2 with the row and col of the next position in the grid
vector<int> Grid::nextPos(int row, int col)
{
	vector<int> newPos;
	if (col + 1 != (int)starBoard[0].size()) //ensure column index is not past the end of board
	{
		newPos.push_back(row);
		newPos.push_back(col + 1);
	}
	else
	{
		newPos.push_back(row + 1);
		newPos.push_back(0);
	}
	return newPos;
}

//Helper reccursive method that returns if there is an adjacent star next to the given position
bool Grid::isAdj(int row, int col, int coorIndex)
{
	vector<vector<int>> coorCheck = { {1,0},{1,1},{1,-1},{0,1},{0,-1},{-1,0},{-1,1},{-1,-1} }; //All combos of adj squares

	int adjRow = row + coorCheck[coorIndex][0];
	int adjCol = col + coorCheck[coorIndex][1];

	//Checks if the next position is valid and won't check an out of bonds position
	if (!(adjRow >= rows || adjRow < 0 || adjCol >= cols || adjCol < 0))
	{
		if (starBoard[adjRow][adjCol] == '*')
		{
			return true;
		}
	}

	//Keep reccursing until checked all 8 surrounding cells
	if (coorIndex != 7)
	{
		return isAdj(row, col, coorIndex + 1);
	}
	return false;
}

//Helper method to check if we can add a star at the given position based on the surrounding stars
//in starboard
bool Grid::canAdd(int row, int col)
{
	int zoneIndex;

	//Loop thru all zones to find which zone that position belongs to
	for (int i = 0; i < (int)allZones.size(); i++)
	{
		if (grid_table[row][col] == allZones[i].getZone())
		{
			zoneIndex = i;
			break;
		}
	}

	//Check thru all conditionals for adding a star (stars in row, stars in coloumn, etc.)
	if ((int)allZones[zoneIndex].getcountStar() == sVal)
	{
		return false;
	}
	else if (rowCount[row] == sVal) 
	{
		return false;
	}
	else if (colCount[col] == sVal)
	{
		return false;
	}
	else if (isAdj(row, col, 0)) //Call to reccursive method to check adjacent cells in starBoard
	{
		return false;
	}
	return true;
}

//Helper method to check if the star board is a completed solution
bool Grid::gridDone(int currS) 
{
	//return if total stars in board is equal to intended stars
	return currS == (int)(allZones.size() * sVal);
}

//Helper method used in CompletSolution() to add a star to starBoard at the given position
void Grid::addStar(int row, int col)
{
	assert(starBoard[row][col] == ' ');
	starBoard[row][col] = '*';
	for (int i = 0; i < (int)allZones.size(); i++)
	{
		if (grid_table[row][col] == allZones[i].getZone())
		{
			allZones[i].updateCount(1);
			rowCount[row]++;
			colCount[col]++;
			break;
		}
	}
}

//Helper method used in CompletSolution() to delete the previous star in starBoard if
//the solution is not possible
void Grid::deletePrevious(int row, int col)
{
	//Ensure there is a star in the intended delte position
	assert(starBoard[row][col] == '*');
	starBoard[row][col] = ' ';

	for (int i = 0; i < (int)allZones.size(); i++)
	{
		if (grid_table[row][col] == allZones[i].getZone())
		{
			//Update all counts accordingly
			allZones[i].updateCount(-1);
			rowCount[row]--;
			colCount[col]--;
			break;
		}
	}
}

//Helper method to create a empty grid of character of row,col
//Starboard will be used to create solutions
gridchar Grid::createStarBoard()
{
	gridchar starBoardLocal;
	for (int i = 0; i < rows; i++)
	{
		vector<char> row;
		for (int j = 0; j < cols; j++)
		{
			row.push_back(' ');
		}
		starBoardLocal.push_back(row);
	}
	return starBoardLocal;
}

//Helper method called in grid initialization to create a helper grid of size rows and cols
//Each cell in this grid is filled with the character of its zone
gridchar Grid::createGrid(vector<gridstr> coordinates)
{
	gridchar grid_table;
	char zoneLetter;
	//Initialize empty grid of proper size
	for (int i = 0; i < rows; i++)
	{
		vector<char> row; //make sure this resets on ever loop
		for (int j = 0; j < cols; j++)
		{
			row.push_back(' ');
		}
		grid_table.push_back(row);
	}
	for (int i = 0; i < (int)coordinates.size(); i++)
	{
		for (int j = 0; j < (int)coordinates[i].size(); j++)
		{
			assert(coordinates[i][j].size() == 2); 
			if (j == 0)
			{
				zoneLetter = coordinates[i][j][0][0];
			}
			else
			{
				//Set each cell in the grid table based on coordinates
				grid_table[stoi(coordinates[i][j][1])][stoi(coordinates[i][j][0])] = zoneLetter; 
			}
		
		}
		
	}
	return grid_table;
}

//Overloaded << operator to print our entire Grid object as all the possible solutions
ostream& operator<<(ostream& COUT, Grid& g)
{
	vector<gridchar> solutionGrid = g.getSolutionBoard();
	gridchar grid_table = g.getGrid();
	COUT << "Number of solutions: " << solutionGrid.size() << "\n" << endl;
	for (int i = 0; i < (int)solutionGrid.size(); i++)
	{
		COUT << "Solution " << i + 1 << ":" << endl;
		for (int j = 0; j < g.getRows(); j++)
		{
			string str = "";
			for (int k = 0; k < g.getCols(); k++)
			{
				if (solutionGrid[i][j][k] == '*')
				{
					str+='@';
				}
				else
				{
					str+=grid_table[j][k];
				}
			}
			COUT << str << endl;
		}
		if (i != (int)solutionGrid.size() - 1)
		{
			COUT << endl;
		}
		
	}
	return COUT;
}
