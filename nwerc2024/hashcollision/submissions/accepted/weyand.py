#!/usr/bin/env python3

n = int(input())
print(f'? {n} 1')
x = int(input())
if x==n:
    print(f'! {n} 1')
    exit(0)
print(f'? {n-x} 1')
y = int(input())
print(f'! {x} {y}')

