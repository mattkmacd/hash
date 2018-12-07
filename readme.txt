The program finds impropper collaboration by using a 2D hash table.
First, we hash all n word sequences and then search for collisions
which we store in the collision class. 

To run:
Have doc set in small directory.
Example command line prompt to run:

./plaigarismCatcher ../Hash/sm_doc_set/ 6 200

In this case, 6 is the amount of n-word sequences and 200 is the cutoff for 
number of collisions to be considered improper. 

The program works for the small doc set and for values of n less than 10.
For values of n greater than 10, and for the medium and large doc sets,
the program segment faults. 