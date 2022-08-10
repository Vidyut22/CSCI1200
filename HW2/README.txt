HOMEWORK 2: SCHEDULE CLASSES


NAME:  < Vidyut Baskar >


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

< https://www.cplusplus.com/search.do?q=setleft
https://www.geeksforgeeks.org/how-to-convert-char-to-string-in-java/
https://www.educba.com/c-plus-plus-setw/ >

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.


ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  < 12 >



DESCRIPTION OF YOUR CREATIVE STATISTIC:

If the third argument is "custom" then the output will consist of all courses
seperated by the day of the week in order. There is an optional fourth argument, which
will only output the courses from the day matching with the fourth argument. 

When outputting multiple days of the week, the tables are printed in day order (Monday-Friday).
Within each table, courses are first organized by earliest start tinme. Courses with the same
start time are alphabetically aranged by course name. If courses have the same course name, they
are finally sorted by course code, i.e. "1100-01" would come before "1100-02".

When outputting one day only, the same sorting rules apply.

If no courses for the days/day are available, the output should look the same as for the 
“empty.txt” case.

Examples: ./course.exe medium2.txt out.txt custom ----------> out_medium2_custom (provided in submission)
	  ./course.exe medium2.txt out.txt custom Tuesday --> out_medium2_custom_Tuesday (provided in submission)

MISC. COMMENTS TO GRADER:  
Optional, please be concise!


