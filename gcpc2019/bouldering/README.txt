Bouldering

Problem:
Given a graph with two labels - distance and weight, find the shortest path from s to t that does not exceed a given weight.
(1-Resource Constrained Shortest Path [https://link.springer.com/chapter/10.1007/0-387-25486-2_2])

Intended Solution:
Dynamic programming over (n,w) with n being the nodes of the graph and w being the maximum weight.

Difficulty: 
about 60% will not be able to solve it.


Potential problems and changes:

I don't really like euclidean distances here, as it set us up for floating point errors.
Possible fixes:

	1. Change to squared euclidean distances or manhattan distance.
		Does not change the problem much, but avoids floating points.
		Needs to find a story justification.

	2. Minimize number of grips used instead of total distance (i.e. all distances 1).
		Makes the problem easier, but might still be interesting.
		Then an O(n^2) approach should work that minimizes stamina used over all paths of n edges.

To make the input format more fun, we could also give the grips as ASCII art like
................
..2........1....
..........1.....
.....4.......1..
................
.......1........
................

with the number being the amount of stamina it takes to use that particular grip
