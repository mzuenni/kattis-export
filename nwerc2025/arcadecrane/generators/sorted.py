#!/usr/bin/env python3
import sys

n, rev = map(int, sys.argv[1:])
print(n)
if rev:
  print(*range(n, 0, -1))
else:
  print(*range(1, n+1))
