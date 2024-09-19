#!/usr/bin/env python3
import random

n = int(input())
random.seed(n)
print(*random.sample(range(1, 101), 3))
