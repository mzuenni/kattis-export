#!/usr/bin/env python3

n, k = int(input()), 0
while 4*k*k < n:
  k += 1

res = [list('.' * (2*k+4)) for _ in range(2*k+4)]

def place(i, j, di, dj):
  res[i][j], res[i+di][j], res[i][j+dj] = 'O##'

for i in range(k+2):
  place(2*i+1, 1, -1, -1)
  place(1, 2*i+1, -1, -1)
  if i > 0:
    place(2*i, -2, 1, 1)

q, r = divmod(n, 2*k)
for i in range(k):
  if i != r//2 or r%2 == 0:
    place(q+2 + (i < r//2), 2*i+2, 1, 1)
  else:
    place(q+3, 2*i+3, -1, -1)

print(2*k+4, 2*k+4)
for s in res:
  print(''.join(s))
