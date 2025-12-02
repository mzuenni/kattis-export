#!/usr/bin/python3
import random
import sys

# Init seed with first argument
random.seed(int(sys.argv[1]))
n = eval(sys.argv[2])
print(n)
p = list(range(1, n + 1))
random.shuffle(p)
print(*p)
