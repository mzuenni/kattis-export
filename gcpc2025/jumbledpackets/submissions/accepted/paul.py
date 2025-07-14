#!/usr/bin/env python3
import itertools

p = input()
n = int(input())
s = input()

if n <= 8:
  a = [''.join(s) for s in itertools.product('01', repeat=n)]
  b = [''.join(s) for s in itertools.product('012', repeat=n)]
  b = [s for s in b if s == min(s[i:] + s[:i] for i in range(n))]

  if p == 'Encode':
    print(b[a.index(s)])
  else:
    for i in range(n):
      t = s[i:] + s[:i]
      if t in b:
        print(a[b.index(t)])
        break
else:
  k = 3
  a = [''.join(s) for s in itertools.product('01', repeat=k)]
  b = ['2' + ''.join(s) for s in itertools.product('012', repeat=k-1)]

  if p == 'Encode':
    print(b[a.index(s[:k])] + s[k:])
  else:
    for i in range(n):
      if s[i] == '2':
        t = s[i:] + s[:i]
        if '2' not in t[k:]:
          print(a[b.index(t[:k])] + t[k:])
