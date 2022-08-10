HOMEWORK 3: CONNECT FOUR


NAME:  < Vidyut Baskar >


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

<
Submitty Vector class implementation files
https://stackoverflow.com/questions/23578455/c-does-the-iterator-need-to-be-deleted
https://www.geeksforgeeks.org/dynamically-allocate-2d-array-c/
 >

Remember: Your implementation for this assignment must be done on your
own, as described in the "Academic Integrity for Homework" handout.


ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  < 15 >



ORDER NOTATION:
For each of the functions below, write the order notation O().
Write each answer in terms of m = the number of rows and n = the
number of columns.  You should assume that calling new [] or delete []
on an array will take time proportional to the number of elements in
the array.

insert (excluding checking for connected four)
O(n)
insert (including checking for connected four)
O(n)
numTokensInColum
O(1)
numTokensInRow
O(n)
numColumns
O(1)
numRows
O(1)
print
O(m)*O(n)
clear
O(n)^2

TESTING & DEBUGGING STRATEGY: 
Discuss your strategy for testing & debugging your program.  
What tools did you use (gdb/lldb/Visual Studio debugger,
Valgrind/Dr. Memory, std::cout & print, etc.)?  How did you test the
"corner cases" of your Matrix class design & implementation?

To debug, I mainly used gdb's breakpoint feature. As a majority of issues were seg faults,
breakpoints were extremley useful to reach the exact line of failure and check variable values
at that point. Additionally, I used Dr. Memory to debug my memory issue. As I understood the error
message (Uninitizalized Read), this only took one run of Dr. Memory to get it right.

To test the "corner cases" of the matrix class, I split my student tests into 4 sections. Horizontal
test, Vertical test, clear board/memory check, copy test. In the horizontal test, I added 25 tokens at various 
places, from 8 cols to the right of the last col, to 20 stories high in one coloumn. All the memory
allocation was correct throughout this, only assigning memory to what needed to be assigned while
outputting the correct connect four. In the vertical test, I stacked two different tokens back to back
until one had a vertical stack of four. It should be noted throughout both these tests, I used assert()
after each line to ensure, an inncorrect connect four had not been determined. For the clear
test, I called the function following the large horizontal test matrix, and it returned to the correct 
size and allocation. Finally, in the copy test, I created two boards, and added data to them while printing
them. After, I set the second board equal to the first and printed the second board. It perfectly
printed what board 1 had previously looked like.

MISC. COMMENTS TO GRADER:  
N/A

