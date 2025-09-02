Two players are playing a game on a huge grid-like board. Both roll dice and have to make exactly as many moves as their respective dice show. Moves are UDLR, but not diagonal.
Determine whether they can end the round in the same cell.

Input:
The players' positions and rolled numbers.

Output:
The coordinates of a cell that both players can reach with exactly the given numbers of moves, or "impossible" if no such cell exists.

Solution outline:
- check if manhattan distance between the points is at most the sum of the rolled numbers
- check if x1+y1+n1 congruent to x2+y2+n2 mod 2
- consider the range of the player w/ the lower number. the corner closest to the other player is a valid point if one exists at all.

Difficulty:
60%
