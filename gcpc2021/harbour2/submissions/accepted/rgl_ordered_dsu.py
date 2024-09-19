#!/usr/bin/env python3

def solve(A, B):
  a = len(A)
  b = len(B)
  n = a + b - 1
  top = a*2+1

  pos = dict()
  for i,x in enumerate(A): pos[x] = 2+2*i
  for i,x in enumerate(B): pos[x] = 2+2*(n-i)

  # DSU -> right
  vr = [i for i in range(n*2+4)]
  pr = [i for i in range(n*2+4)]
  sr = [1 for i in range(n*2+4)]

  # DSU -> left
  vl = [i for i in range(n*2+4)]
  pl = [i for i in range(n*2+4)]
  sl = [1 for i in range(n*2+4)]

  def find_root(x, p):
    if p[x] == x: return x
    p[x] = find_root(p[x], p)
    return p[x]

  def merge(a, b, p, s):
    a = find_root(a, p)
    b = find_root(b, p)
    if a != b:
      if s[a] < s[b]: a, b = b, a
      p[b] = a
      s[a] += 1

  def find_left(x): return None if x-1 < 0 else vl[find_root(x-1, pl)]
  def find_right(x): return None if x+1 >= len(pr) else vr[find_root(x+1, pr)]
  def erase(x):
    lx = find_left(x)
    if lx is not None:
      vl[x] = vl[lx]; merge(x, x-1, vl, sl)
    rx = find_right(x)
    if rx is not None:
      vr[x] = vr[rx]; merge(x, x+1, vr, sr)

  for i in set(range(len(vl))) - set([pos[i] for i in pos]):
    erase(i)

  def is_on_top():
    return find_left(top) == pos[0] or find_right(top) == pos[0]

  res = 1 if is_on_top() else 0
  for i in range(1, n+1):
    erase(pos[i])
    top = pos[i]
    res += 1 if is_on_top() else 0

  return res

if __name__ == '__main__':
  n,a,b = map(int, input().split())
  A = list(map(int, input().split()))
  B = list(map(int, input().split()))
  print(solve(A, B))
