#!/usr/bin/env python3

grids = '''
VVV LLLL NNNUU NNNVVV NNNYYYY
LLV LVVV LLNNU LLNNTV LLNNUYU
LPV PPPV LVZUU LPTTTV LPPPUUU
LPP PPYV LVZZZ LPPUTU LPPLLLL
LPP YYYY LVVVZ LPPUUU LIIIIIL
'''.strip()
grids = [l.split() for l in grids.splitlines()]

def transpose(grid):
  if grid is None:
    return grid
  h, w = len(grid), len(grid[0])
  return [''.join(grid[j][i] for j in range(h)) for i in range(w)]

def solve(h, w):
  if (h*w) % 5 != 0:
    return None
  if h%5 != 0:
    return transpose(solve(w, h))
  if w == 1:
    return ['I'] * 5 if h == 5 else None
  if w == 2:
    if h == 5:
      return None
    res = ['PPP', 'PP']
    for i in range(1, h//5):
      for k in range(2):
        res[k] += 'NNYYYY' if i%2 == k else 'NNNY'
    for k in range(2):
      res[k] += 'P' * (h-len(res[k]))
    return transpose(res)
  return [grids[i%5][2] * ((w-3)//5) + grids[i%5][(w-3)%5] for i in range(h)]

h, w = map(int, input().split())
if grid := solve(h, w):
  print('yes')
  print('\n'.join(grid))
else:
  print('no')
