#!/usr/bin/env python3

a = input().lower()
print(a)
if a.find('sss') != -1:
  print(a.replace('sss', 'sB'))
  print(a.replace('sss', 'Bs'))
elif a.find('ss') != -1:
  print(a.replace('ss', 'B'))
