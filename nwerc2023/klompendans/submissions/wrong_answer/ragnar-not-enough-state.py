#!/usr/bin/env python3
n = int(input())
x1, y1 = map(int, input().split())
x2, y2 = map(int, input().split())
g = [[False] * (n) for _ in range(n)]
g[0][0] = True
q1 = [(0, 0)]
q2 = [(0, 0)]


def steps(x, y, dx, dy):
    l = []
    for dx, dy in [(dx, dy), (dy, dx)]:
        for dx in [dx, -dx]:
            for dy in [dy, -dy]:
                nx, ny = x + dx, y + dy
                if 0 <= nx < n and 0 <= ny < n and not g[nx][ny]:
                    g[nx][ny] = True
                    l.append((nx, ny))
    return l


while q1:
    while q1:
        x, y = q1.pop()
        q2.extend(steps(x, y, x1, y1))
    while q2:
        x, y = q2.pop()
        q1.extend(steps(x, y, x2, y2))
print(sum(sum(row) for row in g))
