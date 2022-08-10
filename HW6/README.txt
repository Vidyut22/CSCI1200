HOMEWORK 6: STAR BATTLE


NAME:  <Vidyut Baskar>



COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

< 
https://brilliant.org/wiki/recursive-backtracking/
https://www.cs.utexas.edu/~scottm/cs307/handouts/recursiveBacktrackingExplanation.htm
 >

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.



ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  <30>



ANALYSIS OF PERFORMANCE OF YOUR ALGORITHM:
(running time order notation & concise paragraph, < 200 words)
The dimensions of the board (w and h) -> O(w*h)
The number of zones (z)? O(z)
The average number of squares in a zone (t) - > O(t) 
The number of stars per zone(s)? -> O(s^2)
etc.

In total, my completeSolution() method would be a runtime of:
O(w*h*z*t*s^2)

The overall performence of my algorithm is relativly bad compared to possible solutions
My algorithms overall idea was to keep adding stars from left to right in the board. If 
you could not add another star, I would go back to the previous star and move it over.
This would continue up the ladder of possibilities checking every combonation of star
possibilities.



DESCRIPTION OF YOUR ADDTIONAL PUZZLES:
Briefly explain the design of the puzzles or dictionaries and what
makes them "interesting" test cases (or why they aren't interesting).

I created 2 aditional puzzles (both not that interesting):

1st: A puzzle of size 1
This test case is interesting as in my program, I needed to include a
special statement to account for a board of 1 cell so that there were no out of bounds errors

2nd: A puzzle where two cells in a zone are not adjacent to another
This wouldn't seem to have any issues (and it didn't), although I noticed
there was not provided puzzle like this an wanted to make sure that was not
a potential error

SUMMARY OF PERFORMANCE OF YOUR PROGRAM ON THE PROVIDED PUZZLES AND 
ON YOUR ADDITIONAL PUZZLES:
For S = 1:
sporcle1/allsolutions -> 1 second
twonot1/allsolutions  -> 4:06
twonot2/allsolutions  -> 1 hr


MISC. COMMENTS TO GRADER:  
(optional, please be concise!)

Because of the way my solver worked, I beleive my runtime was s^2, s being the provided
value. Because of this I beleive in submitty, my solution took too long to complete
for any problem where S>1, as I eventually got the correct solution on my end.