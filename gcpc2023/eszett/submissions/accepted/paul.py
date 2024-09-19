#!/usr/bin/env python3
import re

def f(s):
  return [m.start() for m in re.finditer('(?=ss)', s)]

a = {input().lower()}
for _ in range(10):
  a |= {s[0:i] + 'B' + s[i+2:] for s in a for i in f(s)}
for s in a:
  print(s)
