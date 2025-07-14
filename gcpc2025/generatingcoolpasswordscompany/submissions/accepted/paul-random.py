#!/usr/bin/env python3
import random

random.seed(123)

n = int(input())
for k in range(n):
  print('aA0!' + ''.join(chr(random.randint(33, 126)) for _ in range(8)))
