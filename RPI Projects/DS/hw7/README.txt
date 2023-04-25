HOMEWORK 7: SUPER SMASH BROS. FRAMES


NAME:  < Jary Chen >


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

< ALAC >

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.



ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  < 6 >



ORDER NOTATION ANALYSIS:
Consider the following variables and give the complexity for both running
time AND space along with a short justification for each of the queries below.
For the commands, do not count the space occupied by the database in the space
complexity analysis.

f: The total number of fighters
m: The number of different moves
t: The highest number of moves that have the same starting frame for a particular move

reading the database/populating your initial data structure:

-q (specific move): O(2log(f) + log(m))
3 times map function (find) got called and 2 for f and one for m

-q (all):O((2*7)log(f) + log(m))
each cout takes 2 find function making a total of 7*2
one find function for m

-f: O(log(m) + N^2)
one find function for m and then 2 loops

-s: O(log(m) + N^2)
same thing as f

-d: O(3log(m) + N)
3 find m function used and one loop

MISC. COMMENTS TO GRADER:  
(optional, please be concise!)






