Problem idea: 
In a given maze without loops what is the least amount of steps needed to travel a route of marked positions in given order?
Maze and amount of marked points are too big for anything O(n^2) (for n = width * height)

Solution:
Since there are no loops in the maze you can interprete it as tree with any position as root node.
The total steps is the sum of steps that are needed on the direct routes between consecutive marked positions.
The steps between two marked positions can be calculated by calculating the Lowest Common Ancestor. 
The number of steps is then the sum of the depth differences between A->LCA(A,B) and LCA(A,B)->B

Complexity: 
~ O(n log n) (for n = width * height)

Difficulty:
60-70