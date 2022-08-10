HOMEWORK 9: IMDB SEARCH


NAME:  <Vidyut Baskar>


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

<
https://stackoverflow.com/questions/5455802/how-to-read-a-complete-line-from-the-user-using-cin
https://catherine-leung.gitbook.io/data-strutures-and-algorithms/table/hash-tables/untitled-1-2
http://www.partow.net/programming/hashfunctions/
>

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.



ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  < 8 >


HASH FUNCTION DESCRIPTION:

First, I start off with an arbitrary unsigned int hash -> 1315423911
Then, I check each category of a given query and ensure that the
category is valid. If it is, I add it to an additive string. Once
all categories are checked and added to the string, I loop thru each
character in that string. For each character's ascii value, I add it to
the hash value and bit shift it, then use that as the exponent to the
ongoing hash value: 
	hash ^= ((hash << 5) + totalQuery[i] + (hash >> 2)). 

After all characters have been done, the hash value is complete.

MISC. COMMENTS TO GRADER:  


