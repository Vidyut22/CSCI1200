HOMEWORK 10:  PERFORMANCE & BIG O NOTATION


NAME:  < Vidyut Baskar >


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

<
https://www.geeksforgeeks.org/priority-queue-in-cpp-stl/
 https://forums.codeguru.com/showthread.php?511055-What-s-the-time-complexity-of-sorting-a-list-using-list-sort()
https://stackoverflow.com/questions/7801438/when-does-a-stdpriority-queue-sort-itself
>

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.



ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  < 12 >



COMPLEXITY ANALYSIS
n = number of elements in the input
f = requested number of values in output (first sorted only)
l = maximum length of any string element

Neatly fill in the table below with the Big O Notation for running time.

-------------------------------------------------------------------------------
|          |          | remove   |          | closest  | first f  | longest   |
|          | sort     | dups     | mode     | pair     | sorted   | substr    | 
-------------------------------------------------------------------------------
|          |          |          |          |          |          |           |
| vector   | O(nlogn) | O(n^2)   |O(nlogn)  | O(nlogn) |O(f+nlogn)| O(l^2n^2) |
-------------------------------------------------------------------------------
|          |          |          |          |          |          |           |
| list     | O(nlogn) |O(n^2)    |O(nlogn)  |O(n)      |O(f+nlogn)|O(l^3n^2)  |
-------------------------------------------------------------------------------
|          |          |          |          |          |          |           |
| bst      | O(logn)  |O(n^2)    |O(nlogn)  |O(n)      |O(f+nlogn)|O(l^2nlogn)|
-------------------------------------------------------------------------------
|          |          |          |          |          |          |           |
| pq       | O(nlogn) |X         |O(nlogn)  |O(nlogn)  |O(f+nlogn)|X          |
-------------------------------------------------------------------------------
|          |          |          |          |          |          |           |
| hash     | X        |O(n^2)    |O(n)      |O(n^2)    |X         |O(l^2nlogn)|
-------------------------------------------------------------------------------



RESULTS
For each data type and each operation, run several sufficiently large
tests and collect the operation time output by the program. Organize
these timing measurements in your README.txt file and estimate the
coefficients for the dominant term of your Big ‘O’ Notation.

< 
VECTOR:
	Sort: 1000000,2000000,3000000,4000000,5000000 (# OF STRINGS)
		0.71875,1.40625,2.26562,3.09375,4.18753 (TIME(S))
		Coefficient:8.0 *10^-7

	Remove dups: 5,000,10000,15000,20000,25000 (# OF STRINGS)
			 0.218,0.859,2.089,3.468,5.572 (TIME(S))
			 Coefficient:2.75 *10^-4

	Mode: 1000000,2000000,3000000,4000000,5000000 (# OF STRINGS)
		0.734375,1.54688,2.45312,3.17188,4.21875 (TIME(S))
		Coefficient:1.0 *10^-7

	Closest Pair: 1000000,2000000,3000000,4000000,5000000 (# OF INTEGERS)
			  0.657861,0.90469,1.35676,1.82189,2.59692(TIME(S))
                    Coefficient: 2.5*10^-7
	
	First F Sorted: 1000000,2000000,3000000,4000000,5000000 (# OF STRINGS)
			    0.71875,1.40625,2.26562,3.09375,4.18753 (TIME(S))
			    Coefficient:8.0 *10^-7

LIST:
	Sort: 500000,1000000,1500000,2000000,2500000 (# OF STRINGS)
		0.890625,1.90625,3.09375,4.21875,5.32812 (TIME(S))
		Coefficient:3.8 *10^-6

	Remove dups: 5,000,10000,15000,20000(# OF STRINGS)
			 0.265625,1.10938,2.51562,4.46875(TIME(S))
			 Coefficient:3.91 *10^-4

	Mode: 25000,500000,1000000,1500000,2000000 (# OF STRINGS)
		0.40625 ,0.90625 ,1.90625,3.15625,4.26562  (TIME(S))
		Coefficient:2.23 *10^-6

	Closest Pair: 1000000,2000000,3000000,4000000,5000000 (# OF INTEGERS)
			  1.24862,3.25621,4.89152,6.11316,8.58104(TIME(S))
                    Coefficient: 2.5*10^-6
	
	First F Sorted: 500000,1000000,1500000,2000000,2500000 (# OF STRINGS)
			    0.890625,1.90625,3.09375,4.21875,5.32812 (TIME(S))
			    Coefficient:3.8 *10^-6

BST:
	Sort: 500000,1000000,1500000,2000000,2500000 (# OF STRINGS)
		1.3125,2.76562,3.71875,4.29688,6.1875 (TIME(S))
		Coefficient:3.8 *10^-6

	Remove dups: 5,000,10000,15000,20000(# OF STRINGS)
			 0.15625,0.890625,1.89062,3.01562(TIME(S))
			 Coefficient:4.5 *10^-4

	Mode: 25000,500000,1000000,1500000,2000000 (# OF STRINGS)
		1.25 ,1.71875 ,3.04688,3.89062,5.25  (TIME(S))
		Coefficient:5.44 *10^-6

	Closest Pair: 1000000,2000000,3000000,4000000,5000000 (# OF INTEGERS)
			  2.85942,4.89152,6.11316,8.58104, 12.8429(TIME(S))
                    Coefficient: 1.2*10^-6
	
	First F Sorted: 500000,1000000,1500000,2000000,2500000 (# OF STRINGS)
			    1.3125,2.76562,3.71875,4.29688,6.1875 (TIME(S))
			    Coefficient:3.8 *10^-6

PQ:
	Sort: 500000,1000000,1250000,1500000, (# OF STRINGS)
		1.26562,2.51562,4.01562 ,4.75 (TIME(S))
		Coefficient:2.9 *10^-6

	Remove dups: X

	Mode: 500000,750000,1000000,1250000 (# OF STRINGS)
		1.09375,1.73438 ,2.46875,3.14062,4.46875(TIME(S))
		Coefficient:5.28 *10^-6

	Closest Pair: 1000000,2000000,3000000,4000000,5000000 (# OF INTEGERS)
			  1.2464,2.90561,4.34578,6.39972,6.82981(TIME(S))
                    Coefficient: 1.44*10^-6
	
	First F Sorted: 500000,1000000,1250000,1500000, (# OF STRINGS)
			    1.26562,2.51562,4.01562 ,4.75 (TIME(S))
			    Coefficient:2.9 *10^-6


HASH:
	
	Sort: X

	Remove dups: 5000,7500,10000,12500,15000 (# OF STRINGS)
			0.421875,0.953125,1.71875,2.78125,3.85938 (TIME(S))
			Coefficient:2.13 *10^-4

	Mode: 1000000,2000000,3000000,4000000,5000000 (# OF STRINGS)
		0.765625 ,1.59275 ,2.32812,3.17188,3.84375  (TIME(S))
		Coefficient:5.44 *10^-6

	Closest Pair: 10000,20000,30000,40000,50000 (# OF INTEGERS)
			  1.89028,7.01585,14.4744,23.2102,33.6466(TIME(S))
                    Coefficient: 8.7 *10^-4
	
	First F Sorted: X
>

DISCUSSION
Do these measurements and the overall performance match your predicted
Big ‘O‘ Notation for the data type and operation? Did you update your
initial answers for the Big ‘O‘ Notation of any cell in the table?

Compare the relative coefficients for different data types that have
the same Big ‘O’ Notation for a specific operation. Do these match
your intuition? Are you surprised by any of the results? Will these
results impact your data structure choices for future programming
projects?

Use well-written, complete sentences.  Approximately 250-500 words.  


< 
Overall, I felt that the performance of the data types and their operations 
closely matched my predicted Big ‘O’ notation. I did end up changing one of my cells 
which was BST/remove dups. Initially I had the operation as O (1), but that was before I 
realized the operation needed to output in the same order that the elements were inputted in. 
After seeing a large coefficient of roughly 4.5 *10^-4, I changed this block to O(n^2). As I compared 
various data types and their corresponding operations, a couple stood out to me as 
strong validations of my notation. For example, comparing the closest pair operation for priority 
queue and hash table, I noticed that the average coefficient for P.Q was 1.44*10^-6. Although, the 
coefficient for the hash table was 8.7*10^-4. With a large sample size, the difference between O(nlogn) 
and O(n^2) can be seen here. On the other hand, sticking with closest pair, the coefficient for BST 
is very similar to P.Q at 1.2*10^-6 even though BST is O(n) rather than O(nlogn). This simply shows 
how efficient and almost insignificant log n is even with large data. After looking through the data, 
most of the numbers seemed to intuitively match up and I feel like I have a good grasp on understanding 
the value of using various data structures for various scenarios. In the real world with “Big Data”, 
these ideas become exponentially more important, and this will definitely be a point of focus for my 
future in programming, and soon I’m sure it’ll be something I won’t have to put much thought into but 
rather instinctively know what to do. 
>



MISC. COMMENTS TO GRADER:  
Unfortunatley I didn't have the time to complete longest matching substring for the data structures, but completed
everything else.

