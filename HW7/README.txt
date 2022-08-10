HOMEWORK 7: WORD FREQUENCY MAPS


NAME:  <Vidyut Baskar>


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

<
https://www.cplusplus.com/reference/cstdlib/srand/
https://stackoverflow.com/questions/10232266/using-maps-within-maps-in-c
>

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.



ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  <10>



ANALYSIS OF PERFORMANCE OF YOUR ALGORITHM:
(order notation & concise paragraph, < 200 words)

Overall, my algorithm is quite optimal. Consisting of a modular class 
wordMap, to complete all necessary tasks. In order to generate the user 
desired string, I simply go use the Map structures find() method, to find
the necessary string in O(logn) (fastest possible search). Once I’ve found 
the necessary string, I keep a count of the number of occurrences and 
depending on if it is a random generation of common generation, I designate 
the next word of the string in O(p) run time. The print algorithm was 
also generally optimized. Depending on what the user has requested to be 
printed, I once again use O(logn) to find the necessary string, and then count 
occurrences. For print, the run time changes depending on if the window 
is of size 2 or 3. For size 2, I am counting O(p) occurrences while for 
window of 3, I am counting O(p^2) occurrences. Finally, to load in all the 
words in the text, I simply go word by word taking O(n) run time.

n = total number of words in the sample text file
m = number of unique words in the file
w = width of the sequencing window
p = average number of words observed to follow a particular word
x = the number of words that should be generated

How much memory will the map data structure require, in terms of n, m,
w, p, x (order notation for memory use)?

O(mp)


What is the order notation for performance (running time) of each of
the commands?

load: O(n)

print: O(log(m)+p)

generate most common: O(x*log(m)*mp)

generate random: O(x*log(m)*mp)

quit: O(1)



EXTRA CREDIT
Parsing & using punctuation data, implementation supports *any*
window size, new test cases (describe & summarize performance, but
don't include large datasets with submission).



MISC. COMMENTS TO GRADER:  
(optional, please be concise!)


