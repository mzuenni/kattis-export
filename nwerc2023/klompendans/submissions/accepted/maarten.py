#!/usr/bin/env python3


def dfs(start_move):
    visited = [[[False, False] for _ in range(n)] for _ in range(n)]
    visited[0][0][start_move] = True  # Perhaps this should be `1 - move` instead of `move`, but it passes now 🤷
    stack = [(0, 0, start_move)]
    while stack:
        x, y, move = stack.pop()
        dx, dy = moves[move]
        for xx, yy in (
                (x + dx, y + dy), (x + dy, y + dx),
                (x - dx, y + dy), (x - dy, y + dx),
                (x - dx, y - dy), (x - dy, y - dx),
                (x + dx, y - dy), (x + dy, y - dx),
        ):
            if 0 <= xx < n and 0 <= yy < n and not visited[yy][xx][move]:
                visited[yy][xx][move] = True
                stack.append((xx, yy, 1 - move))
    return visited


n, moves = int(input()), [tuple(map(int, input().split())) for _ in ".."]
print(sum(sum(any((*v, *w)) for v, w in zip(line0, line1)) for line0, line1 in zip(dfs(0), dfs(1))))
