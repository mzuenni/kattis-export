#!/usr/bin/env python3

m, p = 12345**4, 10**18 + 3

def encode(prog):
  res, last = [0], {}
  for i, s in enumerate(prog):
    a = hash(s)
    if len(s) == 1 and s.isalpha():
      a = i-last[s] if s in last else 42
    last[s] = i
    res.append((res[-1]*m + a) % p)
  return res

input()
prog = list(input().split())
hashes = set(x for i in range(len(prog)) for x in encode(prog[i:]))

for _ in range(int(input())):
  input()
  print('yes' if encode(input().split())[-1] in hashes else 'no')
