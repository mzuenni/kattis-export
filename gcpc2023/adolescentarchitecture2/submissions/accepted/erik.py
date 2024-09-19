from decimal import *
sqrt = lambda x: Decimal(x).sqrt()
n = int(input())
ct, st, g, ans, arr = sqrt(3), sqrt(6) - sqrt(2), 0, 0, []
mat = [[1, sqrt(12)-3, 1/sqrt(12)], [st, 1, 1/2], [ct, sqrt(2), 1]] # t, s, c
f = lambda c, a: [a - 1, (st * a).__floor__(), (ct * a).__floor__(), 2][c + (c == 2 and a == 1)]
for _ in range(n):
  s, a = input().split()
  i, a = "tsc".index(s[0]), int(a)
  arr += [(i, a)]
  g ^= f(i, a)
for i, j in arr:
  x = g ^ f(i, j)
  if x == 0:
    ans += j + i != 1
    continue
  ans += (x + 1) < j * mat[i][0]
  ans += (x / st).__ceil__() < min(j * mat[i][1], (x + 1) / st)
  ans += ((x / ct).__ceil__() < min(j * mat[i][2], (x + 1) / ct) and x != 1) or (x == 2 and 1 < j * mat[i][2])
print(ans)