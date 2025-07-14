#!/usr/bin/env python3
import itertools

p = input()
n = int(input())
s = input()

if p == 'Encode':
  i = s.index('1') if '1' in s else n
  print('2' * i + s[i:])
else:
  for i in range(n):
    if s[i] == '2' and s[i-1] != '2':
      print((s[i:] + s[:i]).replace('2', '0'))
      break
  else:
    print(s.replace('2', '0'))
