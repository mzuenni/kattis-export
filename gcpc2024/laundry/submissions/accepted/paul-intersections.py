#!/usr/bin/env python3
import itertools
import math

matrices = []
for v in itertools.combinations(range(1, 8), 3):
  mat = [[x%2, (x//2)%2, x//4] for x in v]
  def cofactor(i, j): 
    return mat[i-1][j-1] * mat[i-2][j-2] - mat[i-2][j-1] * mat[i-1][j-2]
  det = sum(mat[0][j] * cofactor(0, j) for j in range(3))
  if det != 0:
    imat = [[cofactor(j, i)/det for j in range(3)] for i in range(3)]

    for i in range(3):
      for j in range(3):
        assert sum(mat[i][k]*imat[k][j] for k in range(3)) == (i == j)
    matrices.append((v, imat))

for _ in range(int(input())):
  cap = int(input())
  a, b, c, ab, bc, ac, abc = map(int, input().split())
  bound = [(t+cap-1)//cap for t in [0, a, b, a+b+ab, c, a+c+ac, b+c+bc, a+b+c+ab+bc+ac+abc]]

  res = 10**10
  for v, imat in matrices:
    vec = [bound[i] for i in v]
    x, y, z = [sum(imat[i][j]*vec[j] for j in range(3)) for i in range(3)]
    if all(s >= t for s, t in zip([0, x, y, x+y, z, x+z, y+z, x+y+z], bound)):
      res = min(res, math.ceil(x) + math.ceil(y) + math.ceil(z))
  print(res)
