HOMEWORK 9: MINIBLAST


NAME:  < Jary Chen >


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

< LAB ds_hashset and cpp hash function,
 https://www.baeldung.com/cs/hashing-linear-probing#:~:text=Linear%20probing%20is%20one%20of,cell%2C%20we%20insert%20the%20key.
 ^^ website for linear probing >

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.



ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  < insert 15 hours >


HASH FUNCTION DESCRIPTION
I took the hash function from lab;



HASH TABLE IMPLEMENTATION
My table is a vector that holds a pair in each index. In the pair the first is the kmer string
and the second is a vector of ints holding the position it occurs in the genome.




ANALYSIS OF PERFORMANCE OF YOUR ALGORITHM:
(order notation & concise paragraph, < 200 words)

L = length of the genome sequence
q - query length
p - number of different locations where key is found
k - key size (k-mer size)

How much memory will the hash table data structure require (order notation for memory use)?
Since I make each index with a length of kmer a key in my table it will take up O(L) memory use.


What is the order notation for performance (running time) of each of
the commands? What about for the hash table's insert, find, and resize?
-starting with the commend table size and occupancy should all be O(1)
-the genome should be O(L) because I loop through the whole genome and copy the whole
data to another string
-best case for kmer is O(L-K) because the hash function returns a hash_index which is O(1)
-Worst case for kmer will be O(L^2) because it will perform linear probing through the whole table
-the query commend is best case O(q*p) because getPosition will return a hash_index of a position is O(1)
and each pos returned I have to find it in the genome of q length.
-the resize is best case O(L) which is the kmer or genome from the old table, however in the worst case
collision happens often it will be O(L^2)


EXTRA CREDIT
Add a new command to implement the database using one of the other
 data structures that we have covered so far in the course: 
vectors, lists, arrays etc. 

Compare the performance your alternative method to the homework method
by making a table of run times for each of the genomes and query 
sets provided with the homework  and compare the times to build
the index and the times to process the queries. 
Document any new commands you have added in your README file.



MISC. COMMENTS TO GRADER:  
(optional, please be concise!)


