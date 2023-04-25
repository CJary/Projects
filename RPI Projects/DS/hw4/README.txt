HOMEWORK 4: TOOL RENTAL LISTS


NAME:  < Jary Chen>


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

< ALAC tutors, cs mentoring tutor >

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.



ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  < insert 30 hours >



ORDER NOTATION:
Use these variables to analyze each phase of computation.  Briefly
justify your answer for each part.


i = # of different inventory items
c = # of different customers
p = # of pending customers
q = max quantity of a particular tool owned by the store
r = max # of tools rented or requested by a customer at one time
p = total # of pending tool rentals
e = # of rental or return events


Load inventory file: O(i)
Each inventory file line I read it line by line, so O(I) is the total amount of lines I read.

Rental event: O(e*i*i*i*r*r)+O(p*i*i*r*r)
e for the amount of times to perform this rent command
first i is to check if the item can even be rented
second i is to put the person renting it into the inventory object's list
third i is to put the itemid into the customer object's list
both r is to loop to add the amount of inventory and customer object
**after the plus is for waiting same idea

Return event - no pending customer(s):O(e*i*i*i*r*r)
same O notation as RENTAL events but without the pending customer

Return event - with pending customer(s):O(e*i*i*i*r*r)+O(p*i*i*r*r)
same O notation as before but this time with pending customer
almost all member function performs the same thing in inventorycpp and customercpp

Entire program:
O(i) + O(e*i*i*i*r*r)+(p*i*i*r*r) + O(e*i*i*i*r*r) + O(e*i*i*i*r*r) + O(p*i*i*r*r)
total of everything

MISC. COMMENTS TO GRADER:
(optional, please be concise!)
PLS THIS ASSIGNMENT took mad long ik yall nice

