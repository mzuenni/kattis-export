Problem idea: 
Is it possible to create an n-dimensional hyper-step pyramid with a given number of n-dimensional hyper-blocks?


Solution:
The formula to calculate an n-dimensional step pyramid with m steps is:
f(n,m) = 1                   for m = 1
f(n,m) = m^(n-1) + f(n,m-1)  otherwise
Therefore a step pyramid with one more step can be calculated in pretty much O(1).

The next bigger step pyramid of a dimension doesn't need to be checked after the sum of blocks for
the current one already exceeded the given number.
No more dimensions need to be checked if a pyramid with 2 steps already exceeded the given number of blocks.
There are no more than 154512 step pyramids with distinct number of blocks but less than/equal 10^15 blocks

Difficulty:
10-30

Additional info:
Provided program ran on max size input in ~ 0.1 seconds.