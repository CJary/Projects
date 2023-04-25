HOMEWORK 8: B+ TREES


NAME:  < Jary Chen >


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

< ALAC, youtube tree implementation >

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.


ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  < insert 25 hours >


TESTING & DEBUGGING STRATEGY: 
Discuss your strategy for testing & debugging your program.  
What tools did you use (gdb/lldb/Visual Studio debugger,
Valgrind/Dr. Memory, std::cout & print, etc.)?  How did you test the
"corner cases" of your implementation?
I used lldb to find most of the seg fault. Sometimes use dr.memory to see what kind of leaks.
A lot of cout << for recursive situation.
I keep on trying corner cases of splitting the node and then the extra key will go
to the right side. Testing my code over and over again for spliting the node first and then
splitting the parent node.



MISC. COMMENTS TO GRADER:  
(optional, please be concise!)

