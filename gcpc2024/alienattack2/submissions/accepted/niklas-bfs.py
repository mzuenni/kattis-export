#!/bin/python3

# n humans & m friendships.
n, m = map(int, input().split())

# Read friendships.
edges = [set() for _ in range(n)]
for _ in range(m):
    a, b = map(int, input().split())
    a -= 1
    b -= 1
    edges[a].add(b)
    edges[b].add(a)


def bfs(node):
    queue = [node]
    visited = {node}

    while queue:
        node = queue.pop(0)
        for neighbor in edges[node]:
            if neighbor not in visited:
                visited.add(neighbor)
                queue.append(neighbor)

    return visited


res = 0
abducted = set()

for i in range(n):
    if i not in abducted:
        # Run BFS from node i, count the number of visited nodes (component size)
        # and add them to the abducted set to avoid visiting them again.
        visited = bfs(i)
        res = max(res, len(visited))
        abducted |= visited

# The solution is the maximum component size.
print(res)
