#!/usr/bin/env python3

if input() == 'send':
  input()
  s = input()
  for i in range(5):
    print(''.join(str((ord(c) >> i) & 1) for c in s) + '0' * (4-i))
else:
  v = sorted([input() for _ in range(5)], key=len)
  print(''.join(chr(96 + int(''.join(r), 2)) for r in zip(*v)))
