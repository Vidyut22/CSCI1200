using namespace std;
#include <vector>
#include <iostream>
#include <string>
#include "zone.h"

class Grid
{
	typedef vector<Zone> zones;
	typedef vector<vector<char>> gridchar;
	typedef vector<vector<string>> gridstr;
public:

	//DEFAULT CONSTRUCTOR
	Grid(int sVal, int rows, int cols, zones allZones, vector<gridstr> coordinates, bool mode);

	//ACCESSORS
	int getRows()
	{
		return rows;
	}
	int getCols()
	{
		return cols;
	}
	vector<gridchar> getSolutionBoard()
	{
		return solutionsGrid;
	}
	gridchar getGrid()
	{
		return grid_table;
	}

	//Completes all solutions
	bool completeSolution(int row, int col, int currS);
private:
	//HELPER METHODS
	void deletePrevious(int row, int col); 
	void addStar(int row, int col); 
	bool gridDone(int curr);
	bool atLastPos(int row, int col);
	vector<int> nextPos(int row, int col);
	int numCellsLeft(int row, int col);
	bool canAdd(int row, int col);
	bool isAdj(int row, int col, int coorIndex);
	gridchar createGrid(vector<gridstr> coordinates);
	gridchar createStarBoard();

	//MEMBER VARIABLES
	gridchar grid_table;
	gridchar starBoard;
	int sVal;
	int rows;
	int cols;
	vector<int> rowCount;
	vector<int> colCount;
	zones allZones;
	bool mode;
	vector<gridchar> solutionsGrid; //Final vector to store all solutions
	int count;
};
//Overloaded << to print out object Grid
ostream& operator<<(ostream& COUT, Grid& g);