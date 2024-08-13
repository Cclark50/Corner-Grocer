# Corner Grocer Grocery List Program
Author: Christian Clark

This is a project that allows the user to see a condensed list of all items purchased from a grocery store when given an input txt file.
It can give either the numerical value of 1 or all items in the list, or a histogram version of that same list.

In my personal opinion, I feel like the way I wrote the GrocerySales class was well done. Every method written was done with purpose and has it's own place.
In particular, I liked the way I was able to have one method that wrote to any outstream, which allowed me to reuse that code while just passing in either
the file to be written to or the terminal cout stream. 

If I were to impove this program, the first thing I would do is allow for multiple input files to be loaded in at the user's input.
This allows the program to be much more flexible and allow for greater analytical use.
I would also write a function that does the iteration over the list that takes in a function to apply to that list.
This would make it easier to add more functionality to iteration over the list, as we won't have to rewrite the iteration loop on repeat.

The most challenging code to write was definitely reading from the frequency.dat file.
The way I was writing to the dat file had a colon inbetween the name and frequency, so I had to account for it.
In doing so, without the code to check if the current item is an empty string, it would add one extra empty item at the end. 
This caused a headache and the code to check for that scenario is a bit of a hack but it gets the job done with extremely little slowdown or overhead.

The best skill I see being useful from this going forward is definitley reading and writing to files.
I was never too comfortable with that before, and I still am not right now either, but I have improved from my previous classes.

Having all my files do specific things is one way I am making this code as readable as possible.
Comments also help the readability of some of the more complex methods.
I wrote the GrocerySales class to be as self contained as possible as to make it as transferrable as possible outside this project. 
Maintainance should be easy enough, as there is no obscurity in any of my functions and methods. 
They all do their own thing well and adding functions should cause no issues at all.
