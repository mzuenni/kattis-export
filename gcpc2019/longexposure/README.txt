(Note: This is not the same problem as "fastspinning" submitted to NWERC 2018.)

Given axis-aligned rectangles with integer coordinates, consider the subsurfaces created by the (0,0)-centered circles touching the rectangles.
Determine
1. the total surface area of the subsurfaces fully covered by rectangles, as well as
2. the total surface area of all subsurfaces partially covered by rectangles.

Solution outline:
- Consider the number of minimum 1x1 squares intersected by a circle.
  - When the circle gets larger, the circle will "leave" some squares through one of their corners and "enter" the next square through the same corner. Changes like this can be ignored as the affected ring has a surface area of 0.
  - Therefore, the number of squares intersected by a circle only increases when new squares are entered through corners lying on the x or y axis.
  - Number of squares "required" by a circle with radius r is: 8 * floor(r) + 4
  - Squares can accordingly be grouped by the "diagonal" they lie on:
      \\|//
      \\|//
      --+--
      //|\\
      //|\\
- Split up the rectangles.
  - Rectangles lying in more than one quadrant need to be split up.
  - All rectangles are treated as sets of "enter and exit" intervals for each diagonal they intersect.
  - Rectangles far away from the origin can be treated as grey immediately, as the specified number and sizes of rectangles are not enough to cover very large rings.
- Determine for each (relevant) circle whether the number of intervals covered is equal to the required number of 1x1 squares, zero, or in-between.

Complexity:
O(d log d) or O(d log^2 d)
d = n * (w + h)
especially the last step can lead to slight complexity variations depending on the implementation

Difficulty:
97%
