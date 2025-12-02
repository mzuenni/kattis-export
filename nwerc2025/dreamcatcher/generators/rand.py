#!/usr/bin/python3
import random
import sys

random.seed(int(sys.argv[1]))
min_n = int(sys.argv[2])
max_n = int(sys.argv[3])

assert min_n <= max_n
print(random.randint(min_n,max_n))
