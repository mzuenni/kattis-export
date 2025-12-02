#!/usr/bin/env python3

def bin(n, k):
  if n == 0:
    return 1
  if n%2 < k%2:
    return 0
  return bin(n//2, k//2)

def full(k):
  return (1 << k) - 1

def solve(n, k, x):
  bit = 1 << (n-1)
  lmin = full(k)
  rmin = bit | full(k-1)
  if bin(n-1, k-1):
    if bin(n-1, k):
      if x in [lmin, rmin]:
        return x ^ lmin ^ rmin
    else:
      v = solve(n-1, k, lmin)
      if x in [v, rmin]:
        return x ^ v ^ rmin
  if x & bit:
    return solve(n-1, k-1, x ^ bit) ^ bit
  return solve(n-1, k, x)

tc = int(input())
for _ in range(tc):
  h, w, k = map(int, input().split())
  s = ''.join(input() for _ in range(h))[::-1]
  x = int(s.replace('.', '0').replace('#', '1'), 2)
  n, k = h*w, x.bit_count()
  if bin(n, k):
    print("risky", flush=True)
  else:
    def pc(z):
      i, j = divmod(z.bit_length() - 1, w)
      print(i+1, j+1, flush=True)
    y = solve(n, k, x)
    pc(x & ~y)
    pc(y & ~x)
