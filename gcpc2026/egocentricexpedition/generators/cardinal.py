# Using python for more precision

import sys
import random
import math
from decimal import Decimal, getcontext
getcontext().prec = 100

random.seed(int(sys.argv[1]))
min_a = int(sys.argv[2])
max_a = int(sys.argv[3])
direction = int(sys.argv[4]) # mapping 0 -> axis aligned, 1 -> 45 degree

norm_x = [Decimal(0.5).sqrt(), 0][direction]
norm_y = [Decimal(0.5).sqrt(), 1][direction]

tests = []
for a in range(min_a, max_a + 1):
    r = Decimal(a / Decimal(2)).sqrt()
    x = r * norm_x
    y = r * norm_y
    tests.append((x, y))

random.shuffle(tests)
print(len(tests))
for x, y in tests:
    print(format(x, ".25f"), format(y, ".25f"))
