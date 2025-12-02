#!/usr/bin/env python3
import random
from string import ascii_lowercase
import sys

# Init seed with first argument
l = int(sys.argv[1])
r = int(sys.argv[2])
seed = int(sys.argv[3])
random.seed(seed)

n = random.randint(l, r)

print("send")
print(n)
print("".join(random.choice(ascii_lowercase) for i in range(n)))

# write the seed to 'testcase.ans'
f = open("testcase.ans", "w")
with f:
    f.write(f"{seed}\n")
