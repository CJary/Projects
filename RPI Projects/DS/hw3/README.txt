HOMEWORK 3: MATRIX CLASS

NAME:  < Jary Chen >


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

< insert collaborators / resources >
-ALAC tutor

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.


ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  < insert 15 hours >


ORDER NOTATION:
For each of the functions below, write the order notation O().
Write each answer in terms of m = the number of rows and n = the
number of columns.  You should assume that calling new [] or delete []
on an array will take time proportional to the number of elements in
the array.

get O(1)

set O(1)

num_rows O(1)

get_column O(N)

operator<< O(N^2)

quarter  O(N^2)

operator==  O(N^2)

operator!=  O(N^2)

swap_rows O(1)

rref (provided in matrix_main.cpp) O(N^3)



TESTING & DEBUGGING STRATEGY: 
Discuss your strategy for testing & debugging your program.  
What tools did you use (gdb/lldb/Visual Studio debugger,
Valgrind/Dr. Memory, std::cout & print, etc.)?  How did you test the
"corner cases" of your Matrix class design & implementation?
-Lab 4/5 submitty valgrind and Colin** from ALAC
-I test it by commenting and uncommenting some stuff to see which
did the heap error came from.



EXTRA CREDIT: 
Indicate here if you implemented resize() for extra credit.  
Also document the order notation for your resize() function.
Yes O(N^2)


MISC. COMMENTS TO GRADER:  
(optional, please be concise!)


