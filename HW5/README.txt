HOMEWORK 5: UNROLLED LINKED LISTS


NAME:  < Vidyut Baskar >


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

< 
https://stackoverflow.com/questions/10787614/check-if-pointer-to-custom-class-no-longer-exists
https://github.com/DynamoRIO/drmemory/issues/2275
Handout HW5 found on Submitty
 >

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.



ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  < 30 >



TESTING & DEBUGGING STRATEGY:
To debug this assignment, I relied heavily of gdbs debugger. By using this, I was able to keep track of
my values as I iteratated through the unrolled list, something which is impossible to do by print statements.
Additinally, drmemory came useful to determine where my access to memory was being mistooken.

Testing this assignment consisted of 4 major tests beyond the provided test cases:
1. Special Erases
   	a) Adding to the end
	b) Adding in the middle
	c) Erasing to delete
	d) Erase list with 1 element
2. Special Inserts
	a) Insert at end of list
	b) Insert to overflow list and create new node
	c) Insert into half full array of elements
	d) Erasing and Inserting back to back
3. Copy/Assignment
	a) Create 2 lists and set one equal to each other
4. Type Tests  
	a) String list
	b) Char list
	c) Int list



ORDER NOTATION & EVALUATION:
What is the order notation of each of the member functions in your
class? Discuss any differences between the UnrolledLL, dslist, and STL
list classes. Evaluate the memory usage of your initial implementation
in the worst case. Give a specific example sequence of operations
where the data structure is inefficient. What is the average number of
elements per node in this case? 

size(): O(1)
front(): O(1)
back(): O(1)
push_back(): O(1)
pop_back(): O(1)
push_front(): O(1)
pop_front(): O(1)
erase(): O(NUM_ELEMENTS_IN_NODE) worst case
insert(): O(n) worst case, O(NUM_ELEMENTS_IN_NODE) on average

The main diffences between unrolledLL and the other list structures, is the
amoung of memory canges necessary. With an UnrolledLL, you are not required to
shift all elements in your list if there is an erase or insert. This makes them a
very simple operation to accomplish, running in less time. Although, it uses addtional
memory as it does not fill in every slot in between the list elements.

My initial implementaion of UnrolledLL's, memory usage was above the allocation of
the other 2 lists structures. Because, one can erase elements in the middle, those nodes
are not filled with elements leaving unused memory.

In the following scenario, if I were to insert into the 3rd node, I would end up needing to
create a new node with 5 more slots of memory.

MAX NODE CAPACITY: 5 elements
1-1-1-1-1  1-1-1- -  1-1-1-1-1

-------------------------------

1-1-1-1-1  1-1-1- -  1-1-1-1-1  1- - - - -

In my implementation, the average nodes would still be a full node, as I didn't go about
the method of spliting into two nodes if it overflowed.

EXTRA CREDIT:
Improved memory usage implementation.  Discussion as outlined in .pdf.



MISC. COMMENTS TO GRADER:  
Optional, please be concise!

Unfortunately, I wasn't able to fix one memory issue in my program.

The memory issue was : Invalid Heap deletion. After spending hours on determining a solution,
I came to the conclusion that it had something to do with my copy_list method. I'm assuming because I 
pass my assignment list by reference, when the new list gets assigned the same elements, both lists are pointing
to the same address of memory. Because of that, when I delete my allocation of elements in the destructor, for the second list, there
are no more elements as the destructor already got rid of that allocation with the first list. After spending lots of
time on this issue, I could not find a work around. If you are able to point out my mistake
I would love to learn how this could be fixed in the future!
