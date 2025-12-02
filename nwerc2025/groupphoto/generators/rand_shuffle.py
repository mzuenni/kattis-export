#!/usr/bin/python3
import random
import sys

# Generates a random ascending-descending sequence of length n, then picks a
# random subsequence of size k and shuffles that. The result is an input with
# answer k or slightly less.

# In contrast, a random permutation will have answer very close to n

# Init seed with first argument
random.seed(int(sys.argv[1]))
n = int(sys.argv[2])
k = int(sys.argv[3])

def shuff(lst, k):
    indices = random.sample(range(len(lst)), k)
    values = [lst[i] for i in indices]
    random.shuffle(values)
    for idx, val in zip(indices, values):
        lst[idx] = val
    return lst

l = 0
r = 0
p = list(range(1, n+1))
for i in range(n):
  if random.randint(0, 1) == 0:
    p[l] = i + 1
    l = l + 1
  else:
    p[n - r - 1] = i + 1
    r = r + 1

p = shuff(p, k)
print(n)
print(*p)
