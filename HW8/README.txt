HOMEWORK 8: ROPES


NAME:  <Vidyut Baskar>


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

< 
https://www.geeksforgeeks.org/operations-required-to-make-the-string-empty/
https://www.geeksforgeeks.org/ropes-data-structure-fast-string-concatenation/
 >

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.


ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  < 15 >

BALANCED/WORST CASE RUNNIG TIME ANALYSIS:
n = characters in the string of the current Rope (*this)
m = characters in the string of the Rope passed in (for functions that take
    a second rope)
v = longest "value" of a leaf
p = longest path from root to a leaf
Using these variables, state and explain the big-O running time of each 
of the following operations two ways: 1) with a balanced Rope, 2) with an 
extremely unbalanced Rope. Explain what you considered an extremely 
unbalanced rope for the string "Hello my name is Simon".

An extreely unbalanced rope for the above exampled was imagined as if it were a BST,
although each character was greater than the next, meaning that the height of the 
tree was = to the number of characters in the string (22 in this case). The leaf node
would contain the entire string.

Copy Constructor:
1)O(n)
2)O(n)
Construct from Node*:
1)O(n)
2)O(n)
Index:
1)O(logn)
2)O(1)
Report:
1)O(logn+v)
2)O(v)
iterator operator++:
1)O(n)
2)O(n)
Split:
1)O(logn*p)
2)O(1)
Concat:
1)O(n)
2)O(n)

TESTING & DEBUGGING STRATEGY: 
Briefly describe the tests in your StudentTests() function.
How did you test the "corner cases" of your implementation?

There were 2 main corner case tests that I wanted to check through the student tests.
The first and biggest one being the test for split if I was given an index in the middle
of a node. This is a big one as it adds another method into use in order to split that apart.
To test this, I used the same rope provided and chose index 12 which was in the middle of one of
the nodes. The second test was one that could not be tested through the basic tests. It was if
the two indecies given during report were the same. To test this I tested with the same index.

MISC. COMMENTS TO GRADER:  
Unfortunatley I ran out of time and had no opportunity to even try to fix my memory errors...

