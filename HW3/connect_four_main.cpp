using namespace std;
#include <iostream>
#include <string>
#include <cassert>
#include "Board.h"

void SimpleTest(); //Some basic tests
void StudentTest(); //Write your own test cases here
void CopyTest();

int main(){
	SimpleTest();
	std::cout << "Completed all simple tests." << std::endl;

	StudentTest();
	std::cout << "Completed all student tests." << std::endl;

	CopyTest();
	std::cout << "Completed all copy tests." << std::endl;

	return 0;
}

// Do not modify this function - a fresh copy will be used on Submitty
void SimpleTest(){
	Board b("R","Y",".");

	std::cout << "Initial board:" << std::endl << b << std::endl;
	std::cout << "Row 0 has " << b.numTokensInRow(0) << std::endl;
	std::cout << "Row 4 has " << b.numTokensInRow(4) << std::endl;
	std::cout << "Row 5 has " << b.numTokensInRow(5) << std::endl;
	std::cout << "Column 0 has " << b.numTokensInColumn(0) << std::endl;
	std::cout << "Column 3 has " << b.numTokensInColumn(3) << std::endl;
	std::cout << "Column 4 has " << b.numTokensInColumn(4) << std::endl;

	b.insert(0,true);
	std::cout << "Second handout figure" << std::endl << b << std::endl;

	b.insert(1,false);
	b.insert(2,true);
	b.insert(3,true);
	std::cout << "Third handout figure" << std::endl << b;
	std::cout << "Dimensions are " << b.numRows() << " X " << b.numColumns()
			  << std::endl << std::endl;

	b.insert(1,true);
	b.insert(1,false);
	b.insert(1,true);
	b.insert(1,false);
	b.insert(1,true);
	std::cout << "Fourth handout figure" << std::endl << b;
	std::cout << "Dimensions are " << b.numRows() << " X " << b.numColumns()
			  << std::endl << std::endl;

	b.insert(4,true);
	std::cout << "Fifth handout figure" << std::endl << b;
	std::cout << "Dimensions are " << b.numRows() << " X " << b.numColumns()
			  << std::endl << std::endl;

	//Looks ugly if we don't make all tokens the same length, but not required
	Board b2("Puppy","Kitty","-----"); 
	std::string result;
	std::cout << "Starting a new board!" << std::endl;
	std::cout << "Board is now" << std::endl << b2 << std::endl;
	result = b2.insert(1,true);
	std::cout << "Board is now" << std::endl << b2 << std::endl;
	if(result == "-----"){
		std::cout << "No winner yet." << std::endl;
	}
	else{
		std::cout << "The winner is: " << result << std::endl;
	}
	result = b2.insert(1,true);
	std::cout << "Board is now" << std::endl << b2 << std::endl;
	if(result == "-----"){
		std::cout << "No winner yet." << std::endl;
	}
	else{
		std::cout << "The winner is: " << result << std::endl;
	}
	result = b2.insert(1,true);
	std::cout << "Board is now" << std::endl << b2 << std::endl;
	if(result == "-----"){
		std::cout << "No winner yet." << std::endl;
	}
	else{
		std::cout << "The winner is: " << result << std::endl;
	}
	result = b2.insert(1,true);
	std::cout << "Board is now" << std::endl << b2 << std::endl;
	if(result == "-----"){
		std::cout << "No winner yet." << std::endl;
	}
	else{
		std::cout << "The winner is: " << result << std::endl;
	}
}

////////STUDENT CODE//////

//Write your own test cases here
void StudentTest(){
	//Test Horizontal Connect Four (Additionally tests horizontal and vertical resizing on line 111/159)
	cout << "Testing Horizontal Connect Four (Horizontal/Vertical Resizing too)" << endl;
	string winner;
	Board c("1", "2", ".");
	winner = c.insert(0, true);
	cout << c << endl;
	assert(winner != c.getPlayer1Token() || winner != c.getPlayer2Token());
	winner = c.insert(1, false);
	cout << c << endl;
	assert(winner != c.getPlayer1Token() || winner != c.getPlayer2Token());
	winner = c.insert(2, false);
	cout << c << endl;
	assert(winner != c.getPlayer1Token() || winner != c.getPlayer2Token());
	winner = c.insert(6, true);
	cout << c << endl;
	assert(winner != c.getPlayer1Token() || winner != c.getPlayer2Token());
	winner = c.insert(6, true);
	cout << c << endl;
	assert(winner != c.getPlayer1Token() || winner != c.getPlayer2Token());
	winner = c.insert(3, true);
	cout << c << endl;
	assert(winner != c.getPlayer1Token() || winner != c.getPlayer2Token());
	winner = c.insert(3, false);
	cout << c << endl;
	assert(winner != c.getPlayer1Token() || winner != c.getPlayer2Token());
	winner = c.insert(3, false);
	cout << c << endl;
	assert(winner != c.getPlayer1Token() || winner != c.getPlayer2Token());
	winner = c.insert(3, false);
	cout << c << endl;
	assert(winner != c.getPlayer1Token() || winner != c.getPlayer2Token());
	winner = c.insert(3, true);
	cout << c << endl;
	assert(winner != c.getPlayer1Token() || winner != c.getPlayer2Token());
	winner = c.insert(4, false);
	cout << c << endl;
	assert(winner != c.getPlayer1Token() || winner != c.getPlayer2Token());
	winner = c.insert(5, true);
	cout << c << endl;
	assert(winner != c.getPlayer1Token() || winner != c.getPlayer2Token());
	winner = c.insert(5, true);
	cout << c << endl;
	assert(winner != c.getPlayer1Token() || winner != c.getPlayer2Token());
	winner = c.insert(5, false);
	cout << c << endl;
	assert(winner != c.getPlayer1Token() || winner != c.getPlayer2Token());
	winner = c.insert(4, true);
	cout << c << endl;
	assert(winner != c.getPlayer1Token() || winner != c.getPlayer2Token());
	winner = c.insert(2, true);
	cout << c << endl;
	assert(winner != c.getPlayer1Token() || winner != c.getPlayer2Token());
	winner = c.insert(2, true);
	cout << c << endl;
	assert(winner != c.getPlayer1Token() || winner != c.getPlayer2Token());
	winner = c.insert(2, true);
	cout << c << endl;
	assert(winner != c.getPlayer1Token() || winner != c.getPlayer2Token());
	winner = c.insert(2, false);
	cout << c << endl;
	assert(winner != c.getPlayer1Token() || winner != c.getPlayer2Token());
	winner = c.insert(3, true);
	cout << c << endl;
	assert(winner != c.getPlayer1Token() || winner != c.getPlayer2Token());
	winner = c.insert(3, true);
	cout << c << endl;
	assert(winner != c.getPlayer1Token() || winner != c.getPlayer2Token());
	winner = c.insert(3, false);
	cout << c << endl;
	assert(winner != c.getPlayer1Token() || winner != c.getPlayer2Token());
	winner = c.insert(6, false);
	cout << c << endl;
	assert(winner != c.getPlayer1Token() || winner != c.getPlayer2Token());
	winner = c.insert(4, false);
	cout << c << endl;
	cout << winner << " is the winner by horizontal connection!" << endl;
	cout<<"Finished Test\n------------------------"<<endl;
	//Test Clear
	cout << "Testing Clear Board" << endl;
	c.clear();
	cout << c << endl;
	cout << "Board is clear and reset to " << c.numRows() << " x " << c.numColumns() << "!" << endl;
	cout << "Finished Test\n------------------------" << endl;
	//Test Vertical Connect Four
	cout << "Testing Vertical Connect Four" << endl;
	winner = c.insert(0, true);
	cout << c << endl;
	assert(winner != c.getPlayer1Token() || winner != c.getPlayer2Token());
	winner = c.insert(1, false);
	cout << c << endl;
	assert(winner != c.getPlayer1Token() || winner != c.getPlayer2Token());
	winner = c.insert(3, false);
	cout << c << endl;
	assert(winner != c.getPlayer1Token() || winner != c.getPlayer2Token());
	winner = c.insert(2, true);
	cout << c << endl;
	assert(winner != c.getPlayer1Token() || winner != c.getPlayer2Token());
	winner = c.insert(1, false);
	cout << c << endl;
	assert(winner != c.getPlayer1Token() || winner != c.getPlayer2Token());
	winner = c.insert(1, false);
	cout << c << endl;
	assert(winner != c.getPlayer1Token() || winner != c.getPlayer2Token());
	winner = c.insert(2, true);
	cout << c << endl;
	assert(winner != c.getPlayer1Token() || winner != c.getPlayer2Token());
	winner = c.insert(2, true);
	cout << c << endl;
	assert(winner != c.getPlayer1Token() || winner != c.getPlayer2Token());
	winner = c.insert(2, true);
	cout << c << endl;
	cout << winner << " is the winner by vertical connection!" << endl;
	cout << "Finished Test\n------------------------" << endl;
	
}
//Test copy constructur
void CopyTest()
{
	cout << "Copy Constructor" << endl;
	cout << "BOARD 1\n------------------" << endl;
	Board d("X", "Y", "*");
	string winner;
	winner = d.insert(0, true);
	cout << d<< endl;
	assert(winner != d.getPlayer1Token() || winner != d.getPlayer2Token());
	winner = d.insert(1, false);
	cout << d << endl;
	assert(winner != d.getPlayer1Token() || winner != d.getPlayer2Token());
	winner = d.insert(2, false);
	cout << d << endl;
	assert(winner != d.getPlayer1Token() || winner != d.getPlayer2Token());
	winner = d.insert(6, true);
	cout << d << endl;
	assert(winner != d.getPlayer1Token() || winner != d.getPlayer2Token());
	winner = d.insert(6, true);
	cout << d << endl;
	cout << "BOARD 2\n------------------" << endl;
	Board e("1","2",".");
	winner = e.insert(0, true);
	cout << e << endl;
	assert(winner != e.getPlayer1Token() || winner != e.getPlayer2Token());
	winner = e.insert(1, false);
	cout << e << endl;
	assert(winner != e.getPlayer1Token() || winner !=e.getPlayer2Token());
	winner = e.insert(2, false);
	cout << e << endl;
	cout << "SET BOARD 2 EQUAL TO BOARD 1\n------------------" << endl;
	cout << "BOARD 2\n------------------" << endl;
	e = d;
	cout << e << endl;
}

