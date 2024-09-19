#!/usr/bin/env python3

# Uses the walrus operator (s := s + 1), which is a new feature in Python 3.8
# Sorry (but not really sorry) for the code golfing 😇

(n, k), s = map(int, input().split()), 0
c = [(x, y) for y in range(1, n + 1) for x in range(1, n + 1) if (y - x) % 5 == 0 and "h" in input(f"{x} {y}\n")]
["u" in input(f"{x} {y}\n") and (s := s + 1) >= k and exit() for x, y in
 {*((xx, y) for x, y in c for xx in range(x - 4, x + 5)), *((x, yy) for x, y in c for yy in range(y - 4, y + 5))}
 if (x, y) not in c and 1 <= x <= n and 1 <= y <= n]
