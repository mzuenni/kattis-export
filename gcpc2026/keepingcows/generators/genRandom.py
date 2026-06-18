#!/usr/bin/env python3
import random
import sys

# Init seed with first argument
random.seed(int(sys.argv[1]))

min = int(sys.argv[2])
max = int(sys.argv[3])

print(random.randint(min, max))