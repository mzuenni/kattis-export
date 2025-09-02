Problem:
	Assemble a jigsaw puzzle from square shaped pieces with jagged edges. 

Solution:
	- pick an arbitrary piece and place it at (0,0)
	- run a breadth-first-search from this piece, fixing coordinates and
	  orientation of the other pieces
	- find the minimal and maximal x- and y-values
	- check that this is a valid solution:
		- all pieces are reached
		- all positions are distinct
		- the orientations are consistent
		- the pieces form a rectangle
		- edges are of type 0 iff they are on the boundary
	- reconstruct the grid

Time complexity:
	Each step can be done in O(n).

Estimated Difficulty: 70 (% not solved)
	
	The difficulty can be reduced by adding a guarantee that a solution always
	exists. To make it even easier, one could also fix the orientation of the
	pieces. I would estimate these variants at 45 and 30, respectively.
