HOMEWORK 10: DISTANCE FIELDS & FAST MARCHING METHOD


NAME:  < Jary Chen >


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

< ALAC, lab 12 >

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.



ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  < insert 20 hours >



NAIVE ALGORITHM:

Order Notation: O(w^2 * h^2)

Timing Experiment Data:
tiny_5x5.ppm : 0.00s
small_10x10.ppm : 0.00s
squiggle_30x30.ppm : 0.02s
lines_100x100.ppm : 0.68s
data_structures_300x300.ppm : 53.29s
dots_1000x1000.ppm : too long couldn't wait

Discussion:
The naive algorithm basically loops through every pixel
and then for each of the pixel you loop through the whole board again
to find a black pixel. Save the distance from it and do it until all the black
pixel distance was calculated.


IMPROVED ALGORITHM:

Order Notation: O(w * h * p)

Timing Experiment Data:
tiny_5x5.ppm : 0.00s
small_10x10.ppm : 0.00s
squiggle_30x30.ppm : 0.01s
lines_100x100.ppm : 0.07s
data_structures_300x300.ppm : 9.11s
dots_1000x1000.ppm : 1642.14s

Discussion:
The algorithm is basically the same as the naive but it finds all the
black pixels first and then store the location of it in a vector of pairs.
This way it's easier to compare the distance of the current pixel to the black pixel
instead of searching through the whole thing again to find the black pixel.


FAST MARCHING METHOD (with a map):

Order Notation: O(w * h * log(w*h)

Timing Experiment Data:
tiny_5x5.ppm : 0.00s
small_10x10.ppm : 0.00s
squiggle_30x30.ppm : 0.01s
lines_100x100.ppm : 0.04s
data_structures_300x300.ppm : 0.22s
dots_1000x1000.ppm : 2.22s

Discussion:
I loop through the whole grid and then set the value of all the blacks to zero,
set their x and y correctly and then push everything back into the PQ.
I loop through the PQ and pop everytime until there isn't any left.
I loop at the current top of the queue and it's neighbor and set their distance.
Check if already pushed it into the queue.


DISTANCE FIELD VISUALIZATIONS FOR EXTRA CREDIT:




FAST MARCHING METHOD (with a hash table) FOR EXTRA CREDIT:

Order Notation:

Timing Experiment Data:

Discussion:



MISC. COMMENTS TO GRADER:  
Optional, please be concise!






