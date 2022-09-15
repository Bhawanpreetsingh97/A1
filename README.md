//Bhawanpreet Singh
//README.md

Both PART1 and PART2 of the assignment were completed.
Bugs that were encountered were the output was incorrect, but was fixed and correct output is now being posted

After carefully reading the problem I knew the sequence_ data member had to point to some sort of array
because a Points2D object can store multiple points.
Also since we are able to input more points into the object with the use of >> operator, I assumed that
my sequence should be able to grow.
Since arrays are to be a fixed size, I approached this by adding another member variable called capacity,
for which I defined the default value to be 10. Each time a sequence's size would equal the capacity, I
increased the capacity for that object by calling a helper method increaseCapacity. This process is not
meant to happen a lot because it takes time to copy all the elements into a new sequence, deleting the old
sequence and setting the pointer to the newly created sequence. This method is also used in the + operator
overload. In that method, I create a temp object which I return as the result. There is a chance that the
temp object may need to grow.
I had trouble with coding the sum of sequence for c1 and c2 because it was a bit of a thinking process of how to implement the 
code to get the correct sum of the two sequences, also because I was overthinking the implementation that I confused myself.Gradescope kept timing out and i was not getting a result from gradescope.

Other than those methods, I didn't have too much of a difficult time with the other methods. 

Both PART1 and PART2 of the assignment were completed.
Bugs that were encountered were the output was incorrect, but was fixed and correct output is now being posted

