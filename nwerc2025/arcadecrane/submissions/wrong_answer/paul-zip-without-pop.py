#!/usr/bin/env python3

n = int(input())
a = [int(x)-1 for x in input().split()]
res = []

def add_move(i, j):
  res.append((i+1, j+1))
  b = a[i:i+3].copy()
  a[i:i+3] = []
  a[j:j] = b

l, r = 0, n-1
while r-l >= 5:
  il = a.index(l)
  ir = a.index(r)
  if il == l:
    l += 1
  elif ir == r:
    r -= 1
  elif il <= r-2:
    add_move(il, l)
  elif ir >= l+2:
    add_move(ir-2, r-2)
  else:
    add_move(l, r-2)

def search(d):
  if a == list(range(n)):
    print(len(res))
    for m in res:
      print(*m)
    exit(0)
  if d > 0:
    for i in range(l, l+3):
      for j in range(l, l+3):
        if i != j:
          add_move(i, j)
          search(d-1)
          add_move(j, i)

for d in range(9):
  search(d)
