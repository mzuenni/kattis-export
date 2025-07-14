#!/usr/bin/env python3

n = int(input())
for k in range(n):
  print(f'{k:04}{sum(map(int, str(k))) % 10}aA!')
