Problem:
	Solve a logic puzzle similar to the classic Minesweeper game.

Solution:
	- the solution can be reconstructed row by row
	- for every cell, check if the number to the top left is > 0
	- if it is, put an X and subtract 1 from every adjacent cell
	- do a second pass to check if any non-zero numbers remain
	- output the solution

Time complexity: O(h*w)

Estimated Difficulty: 20 (% not solved)
