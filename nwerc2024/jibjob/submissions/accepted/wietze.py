#!/usr/bin/env python3

n = int(input())
data = []
for i in range(n):
    data.append([int(x) for x in input().split()])
for i in range(n):
    print(min(data[i][2], int(1e-8+min([((data[i][0]-data[j][0])**2+(data[i][1]-data[j][1])**2)**0.5 for j in range(n) if data[i][2] < data[j][2]]+[10**18]))))
