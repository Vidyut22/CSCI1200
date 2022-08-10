HOMEWORK 4: Pizza Event SimulaTOr (PESto)


NAME:  < Vidyut Baskar >


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

< 
https://stackoverflow.com/questions/228908/is-listsize-really-on
https://www.cs.rpi.edu/academics/courses/spring22/csci1200/lectures/10_linked_lists.pdf
https://cplusplus.com/reference/list/list/empty/
https://stackoverflow.com/questions/13819451/delete-the-memory-allocated-for-list
>

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.


ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  < 14 >


ORDER NOTATION:
For each function, using the variables:

  c = number of items still being cooked
  d = number of items completely cooked, but not yet added to an order
  m = number of different item names available
  o = number of orders that have not been filled and are not expired
  p = min number of items per order
  q = max number of items per order
  r = run time (inserted by me)

Include a short description of your order notation analysis.

add_order:
O(q+o) --------> loops through the items(q) in the order and also sorts orders(o)
add_item:
O(c) ----------> sorts items in list of items till being cooked(c)
print_orders_by_time:
O(o*q) --------> nested loop, first going through orders(o), then going through items(q) in order
print_orders_by_id:
O(o*q) --------> nested loop, first going through orders(o), then going through items(q) in order
print_kitchen_is_cooking:
O(c) ----------> loops through all items being cooked(c)
print_kitchen_has_completed:
O(d) ----------> loops through all item completed cooking(d)
run_until_next:
O(c*r+o*r+p) -> contains 3 nested while loops running based on requested runtime(r). 2 of which loop 
	      through orders(o) and the third loops items being cooked(c). Aditionally, 
                run_until_next calls CanFillOrder, a method which on average is the minimum 
	      number of items per order(p).
run_for_time:
O(o*c+o*c+p) -> contains 3 nested while loops running on aveerage o*c times. 2 of which loop 
	      through orders(o) and the third loops items being cooked(c). Aditionally, 
                run_until_next calls CanFillOrder, a method which on average is the minimum 
	      number of items per order(p).


MISC. COMMENTS TO GRADER:  
Optional, please be concise!






